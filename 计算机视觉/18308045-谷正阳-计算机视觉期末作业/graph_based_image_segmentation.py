import cv2
import numpy as np
import hashlib
import collections

def Euclid(v1, v2):
    return ((v1 - v2) ** 2).sum() ** 0.5

def Cosine(v1, v2):
    temp = (v1 * v2).sum()
    if temp == 0:
        return float('inf')
    return (np.linalg.norm(v1) * np.linalg.norm(v2)) / temp - 1

def MergeNeareast(img, Id, C, Dis, len_min):
    m, n = Id.shape
    count = 0
    for Idi, Ci in enumerate(C):
        if len(Ci) != 0:
            if len(Ci) < len_min:
                diff_min = float("inf")
                v_min = None
                for y, x in Ci:
                    for dy, dx in ((-1, 0), (-1, 1), (0, 1), (1, 1), (1, 0), (1, -1), (0, -1), (-1, -1)):
                        y2 = y + dy
                        x2 = x + dx
                        if y2 != -1 and y2 != m and x2 != n:
                            Id2 = Id[y2, x2]
                            if Id2 != Idi:
                                diff = Dis(img[y, x], img[y2, x2])
                                if diff < diff_min:
                                    diff_min = diff
                                    v_min = (y2, x2)
                Id_min = Id[v_min]
                C_min = C[Id_min]
                while len(Ci) > 0:
                    vi = Ci.pop()
                    Id[vi] = Id_min
                    C_min.append(vi)
            else:
                count += 1
    return Id, count

def MergeMinimal(img, Id, C, Dis, len_min):
    m, n = Id.shape
    count = 0
    for Idi, Ci in enumerate(C):
        if len(Ci) != 0:
            if len(Ci) < len_min:
                size_min = float("inf")
                v_min = None
                for y, x in Ci:
                    for dy, dx in ((-1, 0), (-1, 1), (0, 1), (1, 1), (1, 0), (1, -1), (0, -1), (-1, -1)):
                        y2 = y + dy
                        x2 = x + dx
                        if y2 != -1 and y2 != m and x2 != n:
                            Id2 = Id[y2, x2]
                            if Id2 != Idi:
                                size = len(C[Id2])
                                if size < size_min:
                                    size_min = size
                                    v_min = (y2, x2)
                Id_min = Id[v_min]
                C_min = C[Id_min]
                while len(Ci) > 0:
                    vi = Ci.pop()
                    Id[vi] = Id_min
                    C_min.append(vi)
            else:
                count += 1
    return Id, count

def Segment(img, k, sigma=0, Merge=MergeNeareast, Dis=Euclid, len_min=50):
    if Dis == Cosine:
        img += 0.01
    kSize = int(np.ceil(4 * sigma) + 1);
    img = cv2.GaussianBlur(img, (kSize, kSize), sigmaX=sigma, sigmaY=sigma);
    if len(img.shape) == 3:
        m, n, _ = img.shape
    elif len(img.shape) == 2:
        m, n = img.shape
    Id = np.zeros((m, n), dtype=np.uint)
    Int = [k] * (m * n)
    C = [None] * (m * n)
    e = list()
    for y in range(m):
        for x in range(n):
            temp = y * n + x
            Id[y, x] = temp
            C[temp] = [(y, x)]
            for dy, dx in ((-1, 1), (0, 1), (1, 1), (1, 0)):
                y2 = y + dy
                x2 = x + dx
                if y2 != -1 and y2 != m and x2 != n:
                    e.append((Dis(img[y, x], img[y2, x2]), (y, x), (y2, x2)))
    e.sort(key=lambda t: t[0])
    for w, v1, v2 in e:
        Id1 = Id[v1]
        Id2 = Id[v2]
        if Id1 != Id2:
            C1 = C[Id1]
            C2 = C[Id2]
            if w <= min(Int[Id1], Int[Id2]):
                while len(C2) > 0:
                    v3 = C2.pop()
                    Id[v3] = Id1
                    C1.append(v3)
                Int[Id1] = w + k / len(C1)
    return Merge(img, Id, C, Dis, len_min)

def Visualize(Id):
    m, n = Id.shape
    img_new = np.zeros((m, n, 3), dtype=np.uint)
    for y in range(m):
        for x in range(n):
            h1 = hashlib.md5(int(Id[y, x]).to_bytes(length=64, byteorder='little', signed=False)).digest()
            h2 = hashlib.md5(h1).digest()
            h3 = hashlib.md5(h2).digest()
            img_new[y, x, 0] = int.from_bytes(h1, byteorder='little', signed=False) % 256
            img_new[y, x, 1] = int.from_bytes(h2, byteorder='little', signed=False) % 256
            img_new[y, x, 2] = int.from_bytes(h3, byteorder='little', signed=False) % 256
    return img_new

def Mask(mask, Id):
    m, n = mask.shape
    count_tot = collections.Counter(Id.flatten())
    count_mask = collections.Counter((Id * mask).flatten())
    Id_fg = set()
    for k in count_mask:
        if k != 0 and count_mask[k] / count_tot[k] > 0.5:
            Id_fg.add(k)
    mask_new = np.zeros((m, n, 3), dtype=np.uint)
    for y in range(m):
        for x in range(n):
            mask_new[y, x, 0] = mask_new[y, x, 1] = mask_new[y, x, 2] = (Id[y, x] in Id_fg) * 255
    mask_temp = mask_new[:, :, 0]
    IOU = np.logical_and(mask_temp, mask).sum() / np.logical_or(mask_temp, mask).sum()
    return mask_new, IOU

def Find_k(img, k_mean, i, sigma=0, Merge=MergeNeareast, Dis=Euclid, len_min=50, count_min=50, count_max=70):
    k = k_mean
    Id, count = Segment(img, k, sigma, Merge, Dis, len_min)
    k_min = 0
    k_max = float('inf')
    if count < count_min:
        cc = 0
        while count < count_min:
            if cc == 4 and Segment(img, 0, sigma, Merge, Dis, len_min)[1] < count_min:
                return k_mean, i, None
            k /= 2
            Id, count = Segment(img, k, sigma, Merge, Dis, len_min)
            cc += 1
        k_min = k
        k_max = k * 2
    elif count > count_max:
        while count > count_max:
            k = k * 2
            Id, count = Segment(img, k, sigma, Merge, Dis, len_min)
        k_min = k / 2
        k_max = k
    if count < count_min or count > count_max:
        while True:
            k = (k_min + k_max) / 2
            Id, count = Segment(img, k, sigma, Merge, Dis, len_min)
            if count < count_min:
                k_max = k
            elif count > count_max:
                k_min = k
            else:
                break
    return (k_mean * i + k) / (i + 1), i + 1, Id
