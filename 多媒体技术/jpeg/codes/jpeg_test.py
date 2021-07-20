import numpy as np
import jpeg
import matplotlib.pyplot as plt
import sys
from getopt import getopt

if len(sys.argv) <= 1:
    print("Please specify input image.")
    exit()
img = plt.imread(sys.argv[1])
output = None
qf = 50
visualize = False
argv = sys.argv[2:]
try:
    opts, args = getopt(argv, "o:q:v:")
    for opt, arg in opts:
        if opt == '-o':
            output = arg
        elif opt == '-q':
            qf = int(arg)
        elif opt == '-v':
            visualize = bool(int(arg))
except:
    print('Just support for opt "-o", "-q" and "-v".')
    exit()

encoder = jpeg.encoder().set_image(img, qf=qf)
decoder = jpeg.decoder()

if visualize:
    fig = plt.figure()
    origin_plt = fig.add_subplot(121)
    origin_plt.imshow(img)
    origin_plt.set_title('Original Image')
    padded_plt = fig.add_subplot(122)
    padded_plt.imshow(encoder.img.round().astype(np.uint8))
    padded_plt.set_title('Padded Image')
    plt.show()

    encoder.RGB2YCbCr()

    Y_padding = np.zeros((encoder.h, encoder.w, 1))
    C_padding = 127.5 * np.ones((encoder.h, encoder.w, 1))
    fig = plt.figure()
    Y_plt = fig.add_subplot(131)
    Y_plt.imshow(decoder.set_image(np.concatenate((encoder.img[:, :, :1], Y_padding, Y_padding), axis=2)).YCbCr2RGB().img.round().astype(np.uint8))
    Y_plt.set_title('Y Channel')
    Cb_plt = fig.add_subplot(132)
    Cb_plt.imshow(decoder.set_image(np.concatenate((C_padding, encoder.img[:, :, 1:2], C_padding), axis=2)).YCbCr2RGB().img.round().astype(np.uint8))
    Cb_plt.set_title('Cb Channel')
    Cr_plt = fig.add_subplot(133)
    Cr_plt.imshow(decoder.set_image(np.concatenate((C_padding, C_padding, encoder.img[:, :, 2:]), axis=2)).YCbCr2RGB().img.round().astype(np.uint8))
    Cr_plt.set_title('Cr Channel')
    plt.show()

    encoder.DCT()

    fig = plt.figure()
    Q_plt = fig.add_subplot(121)
    Q_plt.imshow(decoder.set_image(encoder.img).YCbCr2RGB().img.round().astype(np.uint8))
    Q_plt.set_title('DCTed Image')
    DQ_plt = fig.add_subplot(122)
    DQ_plt.imshow(decoder.set_image(encoder.img, qf=qf).IDCT().YCbCr2RGB().img.round().astype(np.uint8))
    DQ_plt.set_title('IDCTed Image')
    plt.show()

    encoder.quantize()

    fig = plt.figure()
    Q_plt = fig.add_subplot(121)
    Q_plt.imshow(decoder.set_image(encoder.img).YCbCr2RGB().img.round().astype(np.uint8))
    Q_plt.set_title('Quantized Image')
    DQ_plt = fig.add_subplot(122)
    DQ_plt.imshow(decoder.set_image(encoder.img, qf=qf).dequantize().IDCT().YCbCr2RGB().img.round().astype(np.uint8))
    DQ_plt.set_title('IDCTed Dequantized Image')
    plt.show()

if output is not None:
    encoder.encode(img, qf, output)
