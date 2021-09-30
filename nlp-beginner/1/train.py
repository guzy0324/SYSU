import torch
from RottenTomatoes import *
from torch.utils.data import random_split, DataLoader
from SoftMax import *
from torch import optim
from tqdm import tqdm

seed = 0
N = 3
k = 4096
device = "cuda"
ratio = 0.8
C = 5
base_lr = 0.005
max_lr = 0.05
batch_size = 128
batch_size2 = 1024
shuffle = True
epoch = 1000
freq = 10

if __name__ == '__main__':
    torch.manual_seed(seed)
    train = RottenTomatoes('train.tsv', N, k, device)
    train_len = int(ratio * len(train))
    valid_len = len(train) - train_len
    train, valid = random_split(train, [train_len, valid_len])
    model = SoftMax(k, C, device)
    criterion = nn.CrossEntropyLoss()
    optimizer = optim.SGD(model.parameters(), lr=batch_size * base_lr)
    scheduler = optim.lr_scheduler.CyclicLR(optimizer,
                                            base_lr=batch_size * base_lr,
                                            max_lr=batch_size * max_lr)
    train_dataloader = DataLoader(train,
                                  batch_size=batch_size,
                                  shuffle=shuffle)
    valid_dataloader = DataLoader(valid, batch_size=batch_size2, shuffle=False)
    min_loss = float("inf")
    for i in tqdm(range(epoch)):
        if i % freq == 0:
            with torch.no_grad():
                loss = 0
                for input, output in valid_dataloader:
                    action = model(input)
                    loss += criterion(action,
                                      output).item() * len(input) / len(valid)
                print("Epoch", i, "Loss", loss)
                if loss < min_loss:
                    print("Save model")
                    torch.save(model.state_dict(), "SoftMax")
                    min_loss = loss
        for input, output in train_dataloader:
            model.zero_grad()
            action = model(input)
            loss = criterion(action, output)
            loss.backward()
            optimizer.step()
            scheduler.step()
    with torch.no_grad():
        loss = 0
        for input, output in valid_dataloader:
            action = model(input)
            loss += criterion(action, output).item() * len(input) / len(valid)
        print("Epoch", i, "Loss", loss)