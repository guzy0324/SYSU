import matplotlib.pyplot as plt
import sys
from getopt import getopt

if len(sys.argv) <= 1:
    print("Please specify input image.")
    exit()
img = plt.imread(sys.argv[1])
argv = sys.argv[2:]
output = None
try:
    opts, args = getopt(argv, "o::v:")
    for opt, arg in opts:
        if opt == '-o':
            output = arg
except:
    print('Just support for opt "-o".')
    exit()
plt.imsave(output, img, format="gif")
