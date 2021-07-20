import random
import numpy as np
import torch
import torch.nn as nn
import torch.optim as optim
import torch.utils.data as Data
from tqdm import tqdm
import os.path
import csv


SEED = 0
GPU = True

BATCH_SIZE = 512
LR = 0.0001
LAMBDA = 0.5
ALPHA = 0.95
EPOCH = 238786


random.seed(SEED)
torch.manual_seed(SEED)
torch.cuda.manual_seed(SEED)
torch.cuda.manual_seed_all(SEED)
torch.backends.cudnn.deterministic=True


device = torch.device("cuda" if GPU and torch.cuda.is_available() else "cpu")
print((torch.load('model_' + str(BATCH_SIZE) + '_' + str(LR) + '_' + str(LAMBDA) + '_' + str(ALPHA) + '/' + str(EPOCH))['weight'].abs() < 0.01).nonzero())
