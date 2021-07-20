import numpy as np
from queue import PriorityQueue, Queue
from bitstring import BitArray

RGB2YCbCr_a = np.array([[0.299, -0.168935, 0.499813],
                        [0.587, -0.331665, -0.418531],
                        [0.114, 0.50059, -0.081282]])
RGB2YCbCr_b = np.array([[-127.5, 0, 0]])

YCbCr2RGB_a = np.linalg.inv(RGB2YCbCr_a)
YCbCr2RGB_b = -RGB2YCbCr_b

T8 = np.array([[np.cos((2 * j + 1) * i * np.pi / 16) / 2 if i > 0 else 1 / 8 ** 0.5 for j in range(8)] for i in range(8)])
T8_T = T8.T

Q = np.array([[[16, 11, 10, 16, 24, 40, 51, 61],
            [12, 12, 14, 19, 26, 58, 60, 55],
            [14, 13, 16, 24, 40, 57, 69, 56],
            [14, 17, 22, 29, 51, 87, 80, 62],
            [18, 22, 37, 56, 68, 109, 103, 77],
            [24, 35, 55, 64, 81, 104, 113, 92],
            [49, 64, 78, 87, 103, 121, 120, 101],
            [72, 92, 95, 98, 112, 100, 103, 99]],

            [[17, 18, 24, 47, 99, 99, 99, 99],
            [18, 21, 26, 66, 99, 99, 99, 99],
            [24, 26, 56, 99, 99, 99, 99, 99],
            [47, 66, 99, 99, 99, 99, 99, 99],
            [99, 99, 99, 99, 99, 99, 99, 99],
            [99, 99, 99, 99, 99, 99, 99, 99],
            [99, 99, 99, 99, 99, 99, 99, 99],
            [99, 99, 99, 99, 99, 99, 99, 99]],

            [[17, 18, 24, 47, 99, 99, 99, 99],
            [18, 21, 26, 66, 99, 99, 99, 99],
            [24, 26, 56, 99, 99, 99, 99, 99],
            [47, 66, 99, 99, 99, 99, 99, 99],
            [99, 99, 99, 99, 99, 99, 99, 99],
            [99, 99, 99, 99, 99, 99, 99, 99],
            [99, 99, 99, 99, 99, 99, 99, 99],
            [99, 99, 99, 99, 99, 99, 99, 99]]], dtype=np.uint8).transpose(1, 2, 0)
Q1 = np.ones((8, 8, 3), dtype=np.uint8)

def shift_right_subtree(num, edges, heights):
    q = Queue()
    q.put((num, 0))
    table = list()
    while not q.empty():
        num, size = q.get()
        if size == len(table):
            table.append(list())
        table[size].append(num)
        if num in edges:
            l, r = edges[num]
            new_size = size + 1
            q.put((l, new_size))
            q.put((r, new_size))
    cur_level = table.pop()
    while len(table) > 0:
        last_level = table.pop()
        last_level_idx = len(last_level)
        cur_level.sort(key=lambda num:heights[num])
        while len(cur_level) > 0:
            last_level_idx -= 1
            while last_level[last_level_idx] not in edges:
                last_level_idx -= 1
            last_level_num = last_level[last_level_idx]
            r, l = cur_level.pop(), cur_level.pop()
            edges[last_level_num] = [l, r]
            heights[last_level_num] = heights[r] + 1
        cur_level = last_level

def limit_length_15(num, edges, heights):
    if heights[num] > 15:
        st1 = [(num, 15)]
        st2 = [(num, 15)]
        while len(st1) > 0:
            num, limit = st1.pop()
            l, r = edges[num]
            new_limit = limit - 1
            if l in edges:
                st1.append((l, new_limit))
                if heights[l] > new_limit:
                    st2.append((num, limit))
            if r in edges:
                st1.append((r, new_limit))
                if heights[r] > new_limit:
                    st2.append((num, limit))
        while len(st2) > 0:
            num, limit = st2.pop()
            l, r = edges[num]
            height_l, height_r = heights[l], heights[r]
            edges[num] = [l, r] if height_l <= height_r else [r, l]
            heights[num] = max(height_l, height_r) + 1
            if heights[num] > limit:
                rl, rr = edges[r]
                height_rl, height_rr = heights[rl], heights[rr]
                height_r = max(height_l, height_rl) + 1
                height_num = max(height_r, height_rr) + 1
                if height_num < heights[num]:
                    edges[r] = [l, rl]
                    edges[num] = [r, rr]
                    shift_right_subtree(num, edges, heights)

def build_Huffman_table(Huffman_encode, Huffman_table, root, edges, counts):
    pq = PriorityQueue()
    heights = dict()
    for num, count in counts.items():
        pq.put((count, num))
        heights[num] = 0
    while pq.qsize() > 1:
        count1, num1 = pq.get()
        limit_length_15(num1, edges, heights)
        count2, num2 = pq.get()
        limit_length_15(num2, edges, heights)
        new_count = count1 + count2
        root += 1
        edges[root] = [num1, num2]
        shift_right_subtree(root, edges, heights)
        pq.put((new_count, root))
    q = Queue()
    q.put((root, 0))
    code = BitArray('0b0')
    while not q.empty():
        num, size = q.get()
        if num in edges:
            l, r = edges[num]
            new_size = size + 1
            q.put((l, new_size))
            q.put((r, new_size))
        else:
            code += size - len(code)
            Huffman_encode[num] = code
            code = BitArray(uint=code.uint + 1, length=len(code) + (code.int == -1))
            Huffman_table[size - 1] += 1
            Huffman_table.append(num)

class encoder(object):
    def __init__(self):
        self.img = np.array([])
        self.t_h = self.t_w = self.h = self.w = 0
        self.qf = 50
        self.Qx = Q
        self.AC = [list(), list(), list()]
        self.DC = [list(), list(), list()]
        self.DC_Huffman_encode = [dict(), dict()]
        self.DC_Huffman_table = [[0] * 16, [0] * 16]
        self.AC_Huffman_encode = [dict(), dict()]
        self.AC_Huffman_table = [[0] * 16, [0] * 16]
        self.Huffman_table = [self.DC_Huffman_table, self.AC_Huffman_table]

    def encode(self, img, qf=50, path=None):
        return self.set_image(img, qf).RGB2YCbCr().DCT().quantize().RLE().DPCM().DC_Huffman().AC_Huffman().save_image(path)

    def set_image(self, img, qf=50):
        self.t_h, self.t_w = img.shape[:2]
        img = img.copy()
        if img.shape[0] % 8:
            img = np.r_[img, np.zeros((8 - img.shape[0] % 8, img.shape[1], 3))]
        if img.shape[1] % 8:
            img = np.c_[img, np.zeros((img.shape[0], 8 - img.shape[1] % 8, 3))]
        self.img = img
        self.h, self.w = img.shape[:2]
        self.block_num = self.h * self.w // 64
        return self.set_qf(qf)

    def set_qf(self, qf):
        assert 1 <= qf and qf <= 100
        if self.qf != qf:
            self.qf = qf
            if qf >= 50:
                self.scaling_factor = (100 - qf) / 50
            else:
                self.scaling_factor = 50 / qf
            if self.scaling_factor != 0:
                self.Qx = np.ceil((Q * self.scaling_factor)).astype(np.uint8)
            else:
                self.Qx = Q1
        return self

    def RGB2YCbCr(self):
        self.img = ((self.img.reshape(-1, 3)) @ RGB2YCbCr_a).reshape(self.h, self.w, 3) + RGB2YCbCr_b
        return self

    def DCT(self):
        for i in range(0, self.h, 8):
            for j in range(0, self.w, 8):
                for k in (0, 1, 2):
                    self.img[i:i+8, j:j+8, k] = T8 @ self.img[i:i+8, j:j+8, k] @ T8_T
        return self

    def quantize(self):
        for i in range(0, self.h, 8):
            for j in range(0, self.w, 8):
                self.img[i:i+8, j:j+8] = (self.img[i:i+8, j:j+8] / self.Qx).round().astype(np.int16)
        return self

    def RLE(self):
        for k in (0, 1, 2):
            AC = list()
            for i in range(0, self.h, 8):
                for j in range(0, self.w, 8):
                    zero_count = 0
                    for m in range(1, 15):
                        min_m_7 = min(m, 7)
                        for n in range(max(m - 7, 0), min_m_7 + 1):
                            if m % 2:
                                num = int(self.img[i + n, j + m - n, k])
                            else:
                                num = int(self.img[i + m - n, j + n, k])
                            if num == 0:
                                zero_count += 1
                            else:
                                while zero_count > 15:
                                    AC.append((15, 0))
                                    zero_count -= 16
                                AC.append((zero_count, num))
                                zero_count = 0
                    if zero_count != 0:
                        AC.append((0, 0))
            self.AC[k] = AC
        return self

    def DPCM(self):
        for k in (0, 1, 2):
            DC = list()
            last = 0
            for i in range(0, self.h, 8):
                for j in range(0, self.w, 8):
                    cur = int(self.img[i, j, k])
                    DC.append(cur - last)
                    last = cur
            self.DC[k] = DC
        return self

    def DC_Huffman(self):
        for k, DC in enumerate(self.DC):
            if k != 2:
                root = float('-inf')
                edges = dict()
                counts = dict()
            for i in range(self.block_num):
                amplitude = DC[i]
                sign = amplitude > 0
                amplitude = abs(amplitude)
                size = int(np.log2(amplitude)) + 1 if amplitude > 0 else 0
                DC[i] = size, BitArray() if size == 0 else BitArray(uint=amplitude, length=size) if sign else ~BitArray(uint=amplitude, length=size)
                if size not in counts:
                    root = max(size, root)
                    counts[size] = 1
                else:
                    counts[size] += 1
            if k != 1:
                k //= 2
                self.DC_Huffman_encode[k] = dict()
                self.DC_Huffman_table[k] = [0] * 16
                build_Huffman_table(self.DC_Huffman_encode[k], self.DC_Huffman_table[k], root, edges, counts)
        return self

    def AC_Huffman(self):
        for k, AC in enumerate(self.AC):
            if k != 2:
                root = float('-inf')
                edges = dict()
                counts = dict()
            for i in range(len(AC)):
                runlength, amplitude = AC[i]
                sign = amplitude > 0
                amplitude = abs(amplitude)
                size = int(np.log2(amplitude)) + 1 if amplitude > 0 else 0
                symbol1 = (runlength << 4) + size
                AC[i] = symbol1, BitArray() if size == 0 else BitArray(uint=amplitude, length=size) if sign else ~BitArray(uint=amplitude, length=size)
                if symbol1 not in counts:
                    root = max(symbol1, root)
                    counts[symbol1] = 1
                else:
                    counts[symbol1] += 1
            if k != 1:
                k //= 2
                self.AC_Huffman_encode[k] = dict()
                self.AC_Huffman_table[k] = [0] * 16
                build_Huffman_table(self.AC_Huffman_encode[k], self.AC_Huffman_table[k], root, edges, counts)
        return self

    def save_image(self, path):
        if type(path) is str:
            bit_stream = BitArray('0xffd8ffe000104a46494600010101000100010000')

            for i in (0, 1):
                bit_stream += '0xffdb00430' + str(i)
                for byte in self.Qx[:, :, i].reshape(64):
                    bit_stream += BitArray(uint=byte, length=8)

            bit_stream += '0xffc0001108'
            bit_stream += BitArray(uint=self.t_h, length=16)
            bit_stream += BitArray(uint=self.t_w, length=16)
            bit_stream += '0x03011100021101031101'

            for j in (0, 1):
                for i in (0, 1):
                    bit_stream += '0xffc4'
                    bit_stream += BitArray(uint=3 + len(self.Huffman_table[i][j]), length=16)
                    bit_stream += '0x' + str(i) + str(j)
                    for byte in self.Huffman_table[i][j]:
                        bit_stream += BitArray(uint=byte, length=8)

            bit_stream += '0xffda000c03010002110311003f00'

            data = BitArray()
            j_list = [0, 0, 0]
            for i in range(self.block_num):
                for k in (0, 1, 2):
                    H_idx = k >= 1
                    size, amplitude = self.DC[k][i]
                    data += self.DC_Huffman_encode[H_idx][size] + amplitude
                    AC = self.AC[k]
                    AC_Huffman_encode = self.AC_Huffman_encode[H_idx]
                    j = j_list[k]
                    num_count = 1
                    while num_count < 64:
                        symbol1, symbol2 = AC[j]
                        data += AC_Huffman_encode[symbol1] + symbol2
                        j += 1
                        if symbol1 == 0:
                            break
                        num_count += (symbol1 >> 4) + 1
                    j_list[k] = j
            data.replace('0xff', '0xff00', bytealigned=True)
            data += (8 - len(data)) % 8
            bit_stream += data

            bit_stream += '0xffd9'

            try:
                f = open(path, 'wb')
                bit_stream.tofile(f)
            except:
                print('Invalid path.')
                exit()
        return self

class decoder(object):
    def __init__(self):
        self.qf = None

    def decode(self, img, t_h, t_w, qf=50):
        return self.set_image(img, qf).IDCT().dequantize().YCbCr2RGB().resize(t_h, t_w)

    def set_image(self, img, qf=50):
        assert img.shape[0] % 8 == 0 and img.shape[1] % 8 == 0
        self.img = img.copy()
        self.h, self.w = img.shape[:2]
        return self.set_qf(qf)

    def resize(self, t_h, t_w):
        self.img = self.img[:t_h, :t_w]
        return self

    def set_qf(self, qf):
        assert 1 <= qf and qf <= 100
        if self.qf != qf:
            if qf >= 50:
                self.scaling_factor = (100 - qf) / 50
            else:
                self.scaling_factor = 50 / qf
            if self.scaling_factor != 0:
                self.Qx = np.ceil((Q * self.scaling_factor)).astype(np.uint8)
            else:
                self.Qx = Q1
        return self

    def YCbCr2RGB(self):
        self.img = ((self.img.reshape(-1, 3) + YCbCr2RGB_b) @ YCbCr2RGB_a).reshape(self.h, self.w, 3)
        return self

    def IDCT(self):
        for i in range(0, self.h, 8):
            for j in range(0, self.w, 8):
                for k in range(3):
                    self.img[i:i+8, j:j+8, k] = T8_T @ self.img[i:i+8, j:j+8, k] @ T8
        return self

    def dequantize(self):
        for i in range(0, self.h, 8):
            for j in range(0, self.w, 8):
                self.img[i:i+8, j:j+8] *= self.Qx
        return self
