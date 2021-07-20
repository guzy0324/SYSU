import random
import numpy as np
import torch
import torch.nn as nn
import torch.optim as optim
import torch.utils.data as Data
from tqdm import tqdm
import os.path
import csv
import sys


SEED = 0
GPU = True
VALIDATING = True
TESTING = False
TRAIN_SET_RATIO = 0.7
RECURSION = False
NUM_EPOCHS = 1024 * 1024

LAMBDA_LIST = [2.5]
IGNORE_LIST = [28, 31, 39, 44, 47, 81, 96, 101, 102, 154, 155, 159, 170, 188, 225, 240, 241, 250, 261, 286, 330, 338, 347]


random.seed(SEED)
torch.manual_seed(SEED)
torch.cuda.manual_seed(SEED)
torch.cuda.manual_seed_all(SEED)
torch.backends.cudnn.deterministic=True


device = torch.device("cuda" if GPU and torch.cuda.is_available() else "cpu")


with open("train.csv") as f0:
    reader = csv.reader(f0)
    train = [[float(item) for item in row[1:]] for i, row in enumerate(reader) if i > 0]

if VALIDATING:
    tot_train = train
    if not (os.path.exists("train_train.csv") and os.path.exists("train_valid.csv")):
        random.shuffle(tot_train)
        bound = int(len(tot_train) * TRAIN_SET_RATIO)
        with open("train_train.csv", "w", newline='') as f1:
            train = tot_train[:bound]
            writer = csv.writer(f1)
            writer.writerows(train)
        with open("train_valid.csv", "w", newline='') as f1:
            valid = tot_train[bound:]
            writer = csv.writer(f1)
            writer.writerows(valid)
    else:
        with open("train_train.csv") as f:
            reader = csv.reader(f)
            train = [[float(item) for item in row[1:]] for i, row in enumerate(reader) if i > 0]
        with open("train_valid.csv") as f:
            reader = csv.reader(f)
            valid = [[float(item) for item in row[1:]] for i, row in enumerate(reader) if i > 0]
    valid = torch.tensor(valid, device=device)
    valid_x = torch.cat((valid[:, :-1], torch.ones((valid.shape[0], 1), device=device)), 1)
    valid_y = valid[:, -1]

train = torch.tensor(train, device=device)
x = torch.cat((train[:, :-1], torch.ones((train.shape[0], 1), device=device)), 1)
for IGNORE in IGNORE_LIST:
    x[:, IGNORE:IGNORE+1] = 0
y = train[:, -1]
reg = torch.eye(x.shape[1], device=device)
reg[0:1, 0:1] = 0
MSELoss = nn.MSELoss()
f = [0, 0]

for i, LAMBDA in enumerate(LAMBDA_LIST):
    theta = (x.T @ x + LAMBDA * reg).pinverse() @ x.T @ y
    if VALIDATING:
        f[i % 2] = float(MSELoss(valid_x @ theta, valid_y).detach().sqrt())
        sys.stdout.write(str(LAMBDA) + ':' + ' ' + str(f[i % 2]) + '\n')
    if TESTING:
        with open("test.csv") as f0:
            reader = csv.reader(f0)
            test = [[float(item) for item in row[1:]] for i, row in enumerate(reader) if i > 0]
            test = torch.tensor(test, device=device)

        test = torch.cat((test, torch.ones((test.shape[0], 1), device=device)), 1)

        with open('NE_' + str(LAMBDA) + '.csv', 'w', newline='') as f:
            writer = csv.writer(f)
            writer.writerow(['id', 'reference'])
            writer.writerows([[k, float(v)]for k, v in enumerate(test @ theta)])

if VALIDATING and RECURSION:
    w = (5 ** 0.5 - 1) / 2
    a = LAMBDA_LIST[-2] 
    b = LAMBDA_LIST[-1] 
    fa = f[0]
    fb = f[1]
    x1 = b - w * (b - a)
    theta_x1 = (x.T @ x + x1 * reg).pinverse() @ x.T @ y
    fx1 = float(MSELoss(valid_x @ theta_x1, valid_y).detach().sqrt())
    x2 = a + w * (b - a)
    theta_x2 = (x.T @ x + x2 * reg).pinverse() @ x.T @ y
    fx2 = float(MSELoss(valid_x @ theta_x2, valid_y).detach().sqrt())
    for _ in range(NUM_EPOCHS):
        if fx1 <= fx2:
            sys.stdout.write(str(x1) + ':' + ' ' + str(fx1) + '\n')
            b = x2
            x2 = x1
            x1 = b - w * (b - a)
            theta_x1 = (x.T @ x + x1 * reg).pinverse() @ x.T @ y
            fx1 = float(MSELoss(valid_x @ theta_x1, valid_y).detach().sqrt())
        else:
            sys.stdout.write(str(x2) + ':' + ' ' + str(fx2) + '\n')
            a = x1
            x1 = x2
            x2 = a + w * (b - a)
            theta_x2 = (x.T @ x + x2 * reg).pinverse() @ x.T @ y
            fx2 = float(MSELoss(valid_x @ theta_x2, valid_y).detach().sqrt())
