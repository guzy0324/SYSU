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
LR = 0.001
LAMBDA = 0.5
ALPHA = 0.95
EPOCH = 20045 


random.seed(SEED)
torch.manual_seed(SEED)
torch.cuda.manual_seed(SEED)
torch.cuda.manual_seed_all(SEED)
torch.backends.cudnn.deterministic=True


device = torch.device("cuda" if GPU and torch.cuda.is_available() else "cpu")


with open("test.csv") as f0:
    reader = csv.reader(f0)
    test = [[float(item) for item in row[1:]] for i, row in enumerate(reader) if i > 0]
    test = torch.tensor(test, device=device)

model = nn.Linear(test.shape[1], 1).to(device)
model.load_state_dict(torch.load('model_' + str(BATCH_SIZE) + '_' + str(LR) + '_' + str(LAMBDA) + '_' + str(ALPHA) + '/' + str(EPOCH)))

with open('test_' + str(BATCH_SIZE) + '_' + str(LR) + '_' + str(LAMBDA) + '_' + str(ALPHA) + '_' + str(EPOCH) + '.csv', 'w', newline='') as f:
    writer = csv.writer(f)
    writer.writerow(['id', 'reference'])
    writer.writerows([[k, float(v)]for k, v in enumerate(model(test))])

