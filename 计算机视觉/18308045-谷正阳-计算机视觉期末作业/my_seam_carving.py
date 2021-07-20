from typing import Tuple, Optional

import numpy as np
from scipy.ndimage import sobel
from skimage.feature import hog
import imageio

HoG = False
cell_size = 16

record = False
x_map = None
y_map = None
seam_records = None
seam_idx = 1
optimal_order = False
cur_seam_energy = None
energy = None
keep_mask = None

WIDTH_FIRST = 'width-first'
HEIGHT_FIRST = 'height-first'
OPTIMAL_ORDER = 'optimal-order'
VALID_ORDERS = (WIDTH_FIRST, HEIGHT_FIRST, OPTIMAL_ORDER)

FORWARD_ENERGY = 'forward'
BACKWARD_ENERGY = 'backward'
VALID_ENERGY_MODES = (FORWARD_ENERGY, BACKWARD_ENERGY)

DROP_MASK_ENERGY = 1e5
KEEP_MASK_ENERGY = 1e3


def _rgb2gray(rgb: np.ndarray) -> np.ndarray:
    """Convert an RGB image to a grayscale image"""
    coeffs = np.array([0.2125, 0.7154, 0.0721], dtype=np.float32)
    return (rgb @ coeffs).astype(rgb.dtype)


def _get_seam_mask(src: np.ndarray, seam: np.ndarray) -> np.ndarray:
    """Convert a list of seam column indices to a mask"""
    return ~np.eye(src.shape[1], dtype=np.bool)[seam]


def _remove_seam_mask(src: np.ndarray, seam_mask: np.ndarray) -> np.ndarray:
    """Remove a seam from the source image according to the given seam_mask"""
    if src.ndim == 3:
        h, w, c = src.shape
        seam_mask = np.dstack([seam_mask] * c)
        dst = src[seam_mask].reshape((h, w - 1, c))
    else:
        h, w = src.shape
        dst = src[seam_mask].reshape((h, w - 1))
    return dst


def _record_seam(seam: np.ndarray, seam_mask: np.ndarray):
    global x_map, y_map, seam_records, seam_idx
    seam_records[y_map[~seam_mask], x_map[~seam_mask]] = seam_idx
    seam_idx += 1
    x_map = _remove_seam_mask(x_map, seam_mask)
    y_map = _remove_seam_mask(y_map, seam_mask)


def _remove_seam(src: np.ndarray, seam: np.ndarray) -> np.ndarray:
    """Remove a seam from the source image, given a list of seam columns"""
    seam_mask = _get_seam_mask(src, seam)
    dst = _remove_seam_mask(src, seam_mask)
    return dst


def _get_energy(gray: np.ndarray) -> np.ndarray:
    """Get backward energy map from the source image"""
    assert gray.ndim == 2

    gray = gray.astype(np.float32)
    grad_x = sobel(gray, axis=1)
    grad_y = sobel(gray, axis=0)
    energy = np.abs(grad_x) + np.abs(grad_y)
    global HoG
    if not HoG:
        return energy

    fd = hog(gray, orientations=8, pixels_per_cell=(cell_size, cell_size),
            cells_per_block=(1, 1), visualize=False, feature_vector=False)
    fd_max = fd.reshape((fd.shape[0], fd.shape[1], -1)).max(axis=2) + 1
    fd_max = fd_max.repeat(cell_size, axis=0).repeat(cell_size, axis=1)
    fd_max = np.concatenate((fd_max, fd_max[-1:, :].repeat(energy.shape[0] - fd_max.shape[0], axis=0)), axis=0)
    fd_max = np.concatenate((fd_max, fd_max[:, -1:].repeat(energy.shape[1] - fd_max.shape[1], axis=1)), axis=1)
    return energy / fd_max


def _get_backward_seam(energy: np.ndarray) -> np.ndarray:
    """Compute the minimum vertical seam from the backward energy map"""
    assert energy.size > 0 and energy.ndim == 2
    h, w = energy.shape
    cost = energy[0]
    parent = np.empty((h, w), dtype=np.int32)
    base_idx = np.arange(-1, w - 1, dtype=np.int32)

    for r in range(1, h):
        left_shift = np.hstack((cost[1:], np.inf))
        right_shift = np.hstack((np.inf, cost[:-1]))
        min_idx = np.argmin([right_shift, cost, left_shift],
                            axis=0) + base_idx
        parent[r] = min_idx
        cost = cost[min_idx] + energy[r]

    c = np.argmin(cost)
    global optimal_order, cur_seam_energy
    if optimal_order:
        cur_seam_energy = np.min(cost)
    seam = np.empty(h, dtype=np.int32)

    for r in range(h - 1, -1, -1):
        seam[r] = c
        c = parent[r, c]

    return seam


def _get_backward_seams(gray: np.ndarray, num_seams: int) -> np.ndarray:
    """Compute the minimum N vertical seams using backward energy"""
    h, w = gray.shape
    seams_mask = np.zeros((h, w), dtype=np.bool)
    rows = np.arange(0, h, dtype=np.int32)
    idx_map = np.tile(np.arange(0, w, dtype=np.int32), h).reshape((h, w))
    global record, energy, HoG, keep_mask
    if energy is None:
        energy = _get_energy(gray)
    for _ in range(num_seams):
        if keep_mask is not None:
            energy[keep_mask] += KEEP_MASK_ENERGY
        seam = _get_backward_seam(energy)
        seams_mask[rows, idx_map[rows, seam]] = True

        seam_mask = _get_seam_mask(gray, seam)
        gray = _remove_seam_mask(gray, seam_mask)
        idx_map = _remove_seam_mask(idx_map, seam_mask)
        if record:
            _record_seam(seam, seam_mask)
        if keep_mask is not None:
            keep_mask = _remove_seam_mask(keep_mask, seam_mask)

        # Only need to re-compute the energy in the bounding box of the seam
        _, cur_w = energy.shape
        lo = max(0, np.min(seam) - 1)
        pad_lo = 1 if lo > 0 else 0
        if not HoG:
            hi = min(cur_w, np.max(seam) + 1)
            pad_hi = 1 if hi < cur_w - 1 else 0
            mid_block = gray[:, lo - pad_lo:hi + pad_hi]
            _, mid_w = mid_block.shape
            mid_energy = _get_energy(mid_block)[:, pad_lo:mid_w - pad_hi]
            energy = np.hstack((energy[:, :lo], mid_energy, energy[:, hi + 1:]))
        elif cur_w < cell_size:
            HoG = False
            hi = min(cur_w, np.max(seam) + 1)
            pad_hi = 1 if hi < cur_w - 1 else 0
            mid_block = gray[:, lo - pad_lo:hi + pad_hi]
            _, mid_w = mid_block.shape
            mid_energy = _get_energy(mid_block)[:, pad_lo:mid_w - pad_hi]
            energy = np.hstack((energy[:, :lo], mid_energy, energy[:, hi + 1:]))
            HoG = True
        else:
            lo = (lo - pad_lo) // cell_size * cell_size
            if cur_w - lo < 2 * cell_size:
                lo -= cell_size
            mid_block = gray[:, lo:]
            mid_energy = _get_energy(mid_block)
            energy = np.hstack((energy[:, :lo], mid_energy))

    return seams_mask


def _get_forward_seam(gray: np.ndarray) -> np.ndarray:
    """Compute the minimum vertical seam using forward energy"""
    assert gray.size > 0 and gray.ndim == 2
    gray = gray.astype(np.float32)
    h, w = gray.shape

    top_row = gray[0]
    top_row_lshift = np.hstack((top_row[1:], top_row[-1]))
    top_row_rshift = np.hstack((top_row[0], top_row[:-1]))
    dp = np.abs(top_row_lshift - top_row_rshift)

    parent = np.zeros(gray.shape, dtype=np.int32)
    base_idx = np.arange(-1, w - 1, dtype=np.int32)

    global keep_mask
    for r in range(1, h):
        curr_row = gray[r]
        curr_lshift = np.hstack((curr_row[1:], curr_row[-1]))
        curr_rshift = np.hstack((curr_row[0], curr_row[:-1]))
        cost_top = np.abs(curr_lshift - curr_rshift)
        if keep_mask is not None:
            cost_top[keep_mask[r]] += KEEP_MASK_ENERGY

        prev_row = gray[r - 1]
        cost_left = cost_top + np.abs(prev_row - curr_rshift)
        cost_right = cost_top + np.abs(prev_row - curr_lshift)

        dp_left = np.hstack((np.inf, dp[:-1]))
        dp_right = np.hstack((dp[1:], np.inf))

        choices = np.vstack([cost_left + dp_left, cost_top + dp,
                             cost_right + dp_right])
        dp = np.min(choices, axis=0)
        parent[r] = np.argmin(choices, axis=0) + base_idx

    c = np.argmin(dp)
    global optimal_order, cur_seam_energy
    if optimal_order:
        cur_seam_energy = np.min(dp)

    seam = np.empty(h, dtype=np.int32)
    for r in range(h - 1, -1, -1):
        seam[r] = c
        c = parent[r, c]

    return seam


def _get_forward_seams(gray: np.ndarray, num_seams: int) -> np.ndarray:
    """Compute minimum N vertical seams using forward energy"""
    h, w = gray.shape
    seams_mask = np.zeros((h, w), dtype=np.bool)
    rows = np.arange(0, h, dtype=np.int32)
    idx_map = np.tile(np.arange(0, w, dtype=np.int32), h).reshape((h, w))
    global record, keep_mask
    for _ in range(num_seams):
        seam = _get_forward_seam(gray)
        seams_mask[rows, idx_map[rows, seam]] = True
        seam_mask = _get_seam_mask(gray, seam)
        gray = _remove_seam_mask(gray, seam_mask)
        idx_map = _remove_seam_mask(idx_map, seam_mask)
        if record:
            _record_seam(seam, seam_mask)
        if keep_mask is not None:
            keep_mask = _remove_seam_mask(keep_mask, seam_mask)

    return seams_mask


def _get_seams(gray: np.ndarray, num_seams: int, energy_mode: str) -> np.ndarray:
    """Get the minimum N seams from the grayscale image"""
    assert energy_mode in VALID_ENERGY_MODES
    if energy_mode == BACKWARD_ENERGY:
        return _get_backward_seams(gray, num_seams)
    else:
        return _get_forward_seams(gray, num_seams)


def _reduce_width(src: np.ndarray, delta_width: int, energy_mode: str) -> np.ndarray:
    """Reduce the width of image by delta_width pixels"""
    assert src.ndim in (2, 3) and delta_width >= 0
    if src.ndim == 2:
        gray = src
        src_h, src_w = src.shape
        dst_shape = (src_h, src_w - delta_width)
    else:
        gray = _rgb2gray(src)
        src_h, src_w, src_c = src.shape
        dst_shape = (src_h, src_w - delta_width, src_c)

    seams_mask = _get_seams(gray, delta_width, energy_mode)
    dst = src[~seams_mask].reshape(dst_shape)
    return dst


def _expand_width(src: np.ndarray, delta_width: int, energy_mode: str) -> np.ndarray:
    """Expand the width of image by delta_width pixels"""
    assert src.ndim in (2, 3) and delta_width >= 0
    if src.ndim == 2:
        gray = src
        src_h, src_w = src.shape
        dst_shape = (src_h, src_w + delta_width)
    else:
        gray = _rgb2gray(src)
        src_h, src_w, src_c = src.shape
        dst_shape = (src_h, src_w + delta_width, src_c)

    seams_mask = _get_seams(gray, delta_width, energy_mode)
    dst = np.empty(dst_shape, dtype=np.uint8)

    for row in range(src_h):
        dst_col = 0
        for src_col in range(src_w):
            if seams_mask[row, src_col]:
                lo = max(0, src_col - 1)
                hi = src_col + 1
                dst[row, dst_col] = src[row, lo:hi].mean(axis=0)
                dst_col += 1
            dst[row, dst_col] = src[row, src_col]
            dst_col += 1
        assert dst_col == src_w + delta_width

    global energy
    energy = None
    return dst


def _resize_width(src: np.ndarray, width: int, energy_mode: str) -> np.ndarray:
    """Resize the width of image by removing vertical seams"""
    assert src.size > 0 and src.ndim in (2, 3)
    assert width > 0
    assert energy_mode in VALID_ENERGY_MODES

    src_w = src.shape[1]
    if src_w < width:
        dst = _expand_width(src, width - src_w, energy_mode)
    else:
        dst = _reduce_width(src, src_w - width, energy_mode)
    return dst


def _resize_height(src: np.ndarray, height: int, energy_mode: str) -> np.ndarray:
    """Resize the height of image by removing horizontal seams"""
    assert src.ndim in (2, 3) and height > 0
    global record, x_map, y_map, energy, keep_mask
    if energy is not None:
        energy = energy.T
    if keep_mask is not None:
        keep_mask = keep_mask.T
    if record:
        x_map = x_map.T
        y_map = y_map.T

    if src.ndim == 3:
        src = _resize_width(src.transpose((1, 0, 2)), height, energy_mode).transpose((1, 0, 2))
    else:
        src = _resize_width(src.T, height, energy_mode).T

    if energy is not None:
        energy = energy.T
    if keep_mask is not None:
        keep_mask = keep_mask.T
    if record:
        x_map = x_map.T
        y_map = y_map.T
    return src


def _optimal_order(src, width, height, energy_mode):
    assert src.size > 0 and src.ndim in (2, 3)
    assert width > 0 and height > 0
    assert energy_mode in VALID_ENERGY_MODES

    src_h, src_w = src.shape[:2]
    if src_w == width and src_h == height:
        return src
    dw = width - src_w
    w_expand = 1 if dw > 0 else -1
    dw = abs(dw)
    dh = height - src_h
    h_expand = 1 if dh > 0 else -1
    dh = abs(dh)
    state_table = [0] * (dh + 1)

    global record, x_map, y_map, seam_records, seam_idx, energy

    if record:
        state_table[0] = src, 0, energy, x_map, y_map, seam_records, seam_idx
    else:
        state_table[0] = src, 0, energy

    for j in range(1, dh + 1):
        if record:
            dst2, T2, energy, x_map, y_map, seam_records, seam_idx  = state_table[j - 1]
            seam_records = seam_records.copy()

            dst2 = _resize_height(dst2, src_h + h_expand * j, energy_mode)
            T2 += cur_seam_energy

            state_table[j] = dst2, T2, energy, x_map, y_map, seam_records, seam_idx
        else:
            dst2, T2, energy = state_table[j - 1]

            dst2 = _resize_height(dst2, src_h + h_expand * j, energy_mode)
            T2 += cur_seam_energy

            state_table[j] = dst2, T2, energy

    for i in range(1, dw + 1):
        if record:
            dst1, T1, energy, x_map, y_map, seam_records, seam_idx  = state_table[0]
            seam_records = seam_records.copy()

            dst1 = _resize_width(dst1, src_w + w_expand * i, energy_mode)
            T1 += cur_seam_energy

            state_table[0] = dst1, T1, energy, x_map, y_map, seam_records, seam_idx
        else:
            dst1, T1, energy = state_table[0]

            dst1 = _resize_width(dst1, src_w + w_expand * i, energy_mode)
            T1 += cur_seam_energy

            state_table[0] = dst1, T1, energy

        for j in range(1, dh + 1):
            if record:
                dst1, T1, energy, x_map, y_map, seam_records, seam_idx  = state_table[j]
                seam_records = seam_records.copy()

                dst1 = _resize_width(dst1, src_w + w_expand * i, energy_mode)
                T1 += cur_seam_energy
                energy1 = energy
                x_map1 = x_map
                y_map1 = y_map
                seam_records1 = seam_records
                seam_idx1 = seam_idx

                dst2, T2, energy, x_map, y_map, seam_records, seam_idx  = state_table[j - 1]
                seam_records = seam_records.copy()

                dst2 = _resize_height(dst2, src_h + h_expand * j, energy_mode)
                T2 += cur_seam_energy

                if T1 <= T2:
                    state_table[j] = dst1, T1, energy1, x_map1, y_map1, seam_records1, seam_idx1
                else:
                    state_table[j] = dst2, T2, energy, x_map, y_map, seam_records, seam_idx
            else:
                dst1, T1, energy = state_table[j]

                dst1 = _resize_width(dst1, src_w + w_expand * i, energy_mode)
                T1 += cur_seam_energy
                energy1 = energy

                dst2, T2, energy = state_table[j - 1]

                dst2 = _resize_height(dst2, src_h + h_expand * j, energy_mode)
                T2 += cur_seam_energy

                if T1 <= T2:
                    state_table[j] = dst1, T1, energy1
                else:
                    state_table[j] = dst2, T2, energy

    return state_table[-1][0]


def _check_mask(mask: np.ndarray, shape: Tuple[int, int]) -> np.ndarray:
    """Ensure the mask to be a 2D grayscale map of specific shape"""
    mask = np.asarray(mask, dtype=np.bool)
    if mask.ndim != 2:
        raise ValueError('Invalid mask of shape {}: expected to be a 2D '
                         'binary map'.format(mask.shape))
    if mask.shape != shape:
        raise ValueError('The shape of mask must match the image: expected {}, '
                         'got {}'.format(shape, mask.shape))
    return mask


def _check_src(src: np.ndarray) -> np.ndarray:
    """Ensure the source to be RGB or grayscale"""
    src = np.asarray(src, dtype=np.uint8)
    if src.size == 0 or src.ndim not in (2, 3):
        raise ValueError('Invalid src of shape {}: expected an 3D RGB image or '
                         'a 2D grayscale image'.format(src.shape))
    return src


def resize(src: np.ndarray, size: Tuple[int, int],
           energy_mode: str = 'backward', order: str = 'width-first') -> np.ndarray:
    """Resize the image using the content-aware seam-carving algorithm.
    :param src: A source image in RGB or grayscale format.
    :param size: The target size in pixels, as a 2-tuple (width, height)
    :param energy_mode: Policy to compute energy for the source image. Could be
        one of ``backward`` or ``forward``. If ``backward``, compute the energy
        as the gradient at each pixel. If ``forward``, compute the energy as the
        distances between adjacent pixels after each pixel is removed.
    :param order: The order to remove horizontal and vertical seams. Could be
        one of ``width-first`` or ``height-first``. In ``width-first`` mode, we
        remove or insert all vertical seams first, then the horizontal ones,
        while ``height-first`` is the opposite.
    :return: A resized copy of the source image.
    """
    src = _check_src(src)
    src_h, src_w = src.shape[:2]

    width, height = size
    width = int(round(width))
    height = int(round(height))
    if width <= 0 or height <= 0:
        raise ValueError('Invalid size {}: expected > 0'.format(size))
    if width >= 2 * src_w:
        raise ValueError('Invalid target width {}: expected less than twice '
                         'the source width (< {})'.format(width, 2 * src_w))
    if height >= 2 * src_h:
        raise ValueError('Invalid target height {}: expected less than twice '
                         'the source height (< {})'.format(height, 2 * src_h))

    if order not in VALID_ORDERS:
        raise ValueError('Invalid order {}: expected {}'.format(
            order, VALID_ORDERS))

    if energy_mode not in VALID_ENERGY_MODES:
        raise ValueError('Invalid energy mode {}: expected {}'.format(
            energy_mode, VALID_ENERGY_MODES))

    global record, x_map, y_map, seam_records, seam_idx, optimal_order, energy, keep_mask
    if keep_mask is not None:
        keep_mask = _check_mask(keep_mask, (src_h, src_w))

    energy = None
    if record:
        h, w = src.shape[:2]
        x_map = np.tile(np.arange(0, w, dtype=np.int32).reshape((1, w)), (h, 1))
        y_map = np.tile(np.arange(0, h, dtype=np.int32).reshape(h, 1), (1, w))
        seam_records = np.zeros((h, w), dtype=np.int32)
        seam_idx = 1
    if order == WIDTH_FIRST:
        optimal_order = False
        src = _resize_width(src, width, energy_mode)
        src = _resize_height(src, height, energy_mode)
    elif order == HEIGHT_FIRST:
        optimal_order = False
        src = _resize_height(src, height, energy_mode)
        src = _resize_width(src, width, energy_mode)
    else:
        optimal_order = True
        src = _optimal_order(src, width, height, energy_mode)

    return src


def remove_object(src: np.ndarray, drop_mask: np.ndarray) -> np.ndarray:
    """Remove an object on the source image.
    :param src: A source image in RGB or grayscale format.
    :param drop_mask: A binary object mask to remove.
    :return: A copy of the source image where the drop_mask is removed.
    """
    src = _check_src(src)

    drop_mask = _check_mask(drop_mask, src.shape[:2])

    global keep_mask
    if keep_mask is not None:
        keep_mask = _check_mask(keep_mask, src.shape[:2])

    gray = src if src.ndim == 2 else _rgb2gray(src)

    while drop_mask.any():
        energy = _get_energy(gray)
        energy[drop_mask] -= DROP_MASK_ENERGY
        if keep_mask is not None:
            energy[keep_mask] += KEEP_MASK_ENERGY
        seam = _get_backward_seam(energy)
        seam_mask = _get_seam_mask(src, seam)
        gray = _remove_seam_mask(gray, seam_mask)
        drop_mask = _remove_seam_mask(drop_mask, seam_mask)
        src = _remove_seam_mask(src, seam_mask)
        if keep_mask is not None:
            keep_mask = _remove_seam_mask(keep_mask, seam_mask)

    return src

def resize_as_record(src: np.ndarray, size: Tuple[int, int]) -> np.ndarray:
    src = _check_src(src)
    src_h, src_w = src.shape[:2]

    width, height = size
    width = int(round(width))
    height = int(round(height))
    if (height < src_h and width == src_w) or (width < src_w and height == src_h):
        num_seams = max(src_h - height, src_w - width)
        seams_mask = np.logical_or(seam_records == 0, seam_records > num_seams)
        src = src[seams_mask].reshape(height, width, -1)
    return src


def generate_gif(src, path):
    global seam_records

    dst_h, dst_w = seam_records.shape
    dst = src[:, :, ::-1]
    seam_records = np.dstack([seam_records] * 3)
    with imageio.get_writer(path, mode="I") as writer: 
        writer.append_data(dst)
        for j in range(1, seam_records.max() + 1):
            mask = seam_records != j
            temp = (~mask).sum() / 3
            dh = int(temp == dst_w)
            dw = int(temp == dst_h)
            dst_h -= dh
            dst_w -= dw
            if dh:
                dst = dst.transpose(1, 0, 2)[mask.transpose(1, 0, 2)].reshape(dst_w, dst_h, 3).transpose(1, 0, 2)
                seam_records = seam_records.transpose(1, 0, 2)[mask.transpose(1, 0, 2)].reshape(dst_w, dst_h, 3).transpose(1, 0, 2)
            else:
                dst = dst[mask].reshape(dst_h, dst_w, 3)
                seam_records = seam_records[mask].reshape(dst_h, dst_w, 3)
            writer.append_data(dst)
