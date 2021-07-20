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
VALIDATING = True
SAVING = False
TRAIN_SET_RATIO = 0.7
NUM_EPOCHS = 2048
FREQ = 50

BATCH_SIZE = 512
LR = 0.005
LAMBDA = 0.5
ALPHA = 0.95


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
    valid_x = valid[:, :-1]
    valid_y = valid[:, -1]

if SAVING:
    if not os.path.exists('model_' + str(BATCH_SIZE) + '_' + str(LR) + '_' + str(LAMBDA) + '_' + str(ALPHA)):
        os.mkdir('model_' + str(BATCH_SIZE) + '_' + str(LR) + '_' + str(LAMBDA) + '_' + str(ALPHA))

train = torch.tensor(train, device=device)
train = Data.TensorDataset(train[:, :-1], train[:, -1])
train_loader = Data.DataLoader(dataset=train, batch_size=BATCH_SIZE, shuffle=True)


model = nn.Linear(train.tensors[0].shape[1], 1).to(device)
optim = optim.Adam(params=model.parameters(), lr=LR)
MSELoss = nn.MSELoss()


with open('loss_' + str(BATCH_SIZE) + '_' + str(LR) + '_' + str(LAMBDA) + '_' + str(ALPHA) + '.txt', 'w') as f:
    pass

for epoch in tqdm(range(NUM_EPOCHS)):
    for (batch_x, batch_y) in train_loader:
        EL = MSELoss(model(batch_x).flatten(), batch_y)
        params = torch.cat([p.flatten() for p in model.parameters()])
        loss = EL / 2 + LAMBDA * ((1 - ALPHA) * params.square() / 2 + ALPHA * params.abs()).mean()
        optim.zero_grad()
        loss.backward()
        optim.step()
    if epoch % FREQ == 0:
        with open('loss_' + str(BATCH_SIZE) + '_' + str(LR) + '_' + str(LAMBDA) + '_' + str(ALPHA) + '.txt', 'a') as f:
            f.write('epoch: ' + str(epoch) + '\n')
            f.write('train: ' + str(float(EL.sqrt())) + '\n')
            if VALIDATING:
                f.write('valid: ' + str(float(MSELoss(model(valid_x).flatten(), valid_y).sqrt())) + '\n')
            if SAVING:
                torch.save(model.state_dict(), 'model_' + str(BATCH_SIZE) + '_' + str(LR) + '_' + str(LAMBDA) + '_' + str(ALPHA) + '/' + str(epoch))

with open('loss_' + str(BATCH_SIZE) + '_' + str(LR) + '_' + str(LAMBDA) + '_' + str(ALPHA) + '.txt', 'a') as f:
    f.write('epoch: ' + str(epoch) + '\n')
    f.write('train: ' + str(float(EL.sqrt())) + '\n')
    if VALIDATING:
        f.write('valid: ' + str(float(MSELoss(model(valid_x).flatten(), valid_y).sqrt())) + '\n')
    if SAVING:
        torch.save(model.state_dict(), 'model_' + str(BATCH_SIZE) + '_' + str(LR) + '_' + str(LAMBDA) + '_' + str(ALPHA) + '/' + str(epoch))
