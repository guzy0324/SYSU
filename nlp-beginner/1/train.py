import numpy as np
import torch
from RottenTomatoes import *
from torch.utils.data import random_split, DataLoader
from SoftMax import *
from torch import optim
from torch_lr_finder import LRFinder
from tqdm import tqdm

seed = 0
N = 3
k = 4096
device = "cuda"
ratio = 0.8
C = 5
batch_size = 128
batch_size2 = 1024
start_lr = 0.9
end_lr = 70
num_iter = 1000
shuffle = True
find_lr = False
epoch = 1000
freq = 10

if __name__ == '__main__':
    np.random.seed(seed)
    torch.manual_seed(seed)
    data = RottenTomatoes('train.tsv', N, k, device)
    train_len = int(ratio * len(data))
    valid_len = len(data) - train_len
    train, valid = random_split(data, [train_len, valid_len])
    model = SoftMax(k, C, device)
    # criterion = nn.CrossEntropyLoss(data.weight)
    criterion = nn.CrossEntropyLoss()
    optimizer = optim.SGD(model.parameters(), lr=start_lr)
    train_dataloader = DataLoader(train,
                                  batch_size=batch_size,
                                  shuffle=shuffle)
    valid_dataloader = DataLoader(valid, batch_size=batch_size2, shuffle=False)
    if find_lr:
        lr_finder = LRFinder(model, optimizer, criterion, device="cuda")
        lr_finder.range_test(train_dataloader,
                             valid_dataloader,
                             start_lr=start_lr,
                             end_lr=end_lr,
                             num_iter=num_iter)
        lr_finder.plot()
        lr_finder.reset()
        exit()
    scheduler = optim.lr_scheduler.CyclicLR(optimizer,
                                            base_lr=start_lr,
                                            max_lr=end_lr)
    min_acc = -1
    for i in tqdm(range(epoch)):
        if i % freq == 0:
            with torch.no_grad():
                acc = 0
                for input, output in valid_dataloader:
                    action = model(input)
                    acc += (output == action.argmax(axis=1)).sum().item()
                acc = acc / len(valid)
                print("Epoch", i, "Acc", acc)
                if acc > min_acc:
                    print("Save model")
                    torch.save(model.state_dict(), "SoftMax")
                    min_acc = acc
        for input, output in train_dataloader:
            model.zero_grad()
            action = model(input)
            loss = criterion(action, output)
            loss.backward()
            optimizer.step()
            scheduler.step()
    with torch.no_grad():
        acc = 0
        for input, output in valid_dataloader:
            action = model(input)
            acc += (output == action.argmax(axis=1)).sum().item()
        acc = acc / len(valid)
        print("Epoch", i, "Acc", acc)
        if acc > min_acc:
            print("Save model")
            torch.save(model.state_dict(), "SoftMax")
            min_acc = acc