# python: 3.5.2
# encoding: utf-8

import numpy as np
import torch
from torch import nn
from tqdm import tqdm
from torch import optim

Elinear = nn.MSELoss(reduction='sum')

Elogistic = nn.SoftMarginLoss(reduction='sum')


def ESVM(y, t):
    return (1 - y * t).clamp(min=0).sum()


epoch = 10000
lr = 1e-6
Lambda = 1e-2
criterion = ESVM
freq = 1000


def load_data(fname):
    """
    载入数据。
    """
    with open(fname, 'r') as f:
        data = []
        line = f.readline()
        for line in f:
            line = line.strip().split()
            x1 = float(line[0])
            x2 = float(line[1])
            t = int(line[2])
            data.append([x1, x2, t])
        return np.array(data)


def eval_acc(label, pred):
    """
    计算准确率。
    """
    return np.sum(label == pred) / len(pred)


class SVM():
    """
    SVM模型。
    """
    def __init__(self):
        # 请补全此处代码
        self.linear = nn.Linear(2, 1)
        self.optimizer = optim.SGD(self.linear.parameters(),
                                   lr=lr,
                                   weight_decay=Lambda)

    def train(self, data_train):
        """
        训练模型。
        """

        # 请补全此处代码
        x1, x2, t = zip(*data_train)
        x = torch.cat((torch.tensor(x1, dtype=torch.float32).reshape(
            (-1, 1)), torch.tensor(x2, dtype=torch.float32).reshape((-1, 1))),
                      dim=1)
        self.x_mean = x.mean()
        self.x_std = x.std()
        x = (x - self.x_mean) / self.x_std
        t = torch.tensor(t, dtype=torch.float32).reshape(-1, 1)
        for i in tqdm(range(epoch)):
            self.optimizer.zero_grad()
            y = self.linear(x)
            loss = criterion(y, t)
            loss.backward()
            self.optimizer.step()
            if i % freq == 0:
                print(loss.item())

    def predict(self, x):
        """
        预测标签。
        """

        # 请补全此处代码
        return torch.where(
            self.linear((torch.tensor(x, dtype=torch.float32) - self.x_mean) /
                        self.x_std) > 0, 1., -1.).reshape(-1).numpy()


if __name__ == '__main__':
    # 载入数据，实际实用时将x替换为具体名称
    train_file = 'data/train_linear.txt'
    test_file = 'data/test_linear.txt'
    data_train = load_data(train_file)  # 数据格式[x1, x2, t]
    data_test = load_data(test_file)

    # 使用训练集训练SVM模型
    torch.manual_seed(0)
    svm = SVM()  # 初始化模型
    svm.train(data_train)  # 训练模型

    # 使用SVM模型预测标签
    x_train = data_train[:, :2]  # feature [x1, x2]
    t_train = data_train[:, 2]  # 真实标签
    t_train_pred = svm.predict(x_train)  # 预测标签
    x_test = data_test[:, :2]
    t_test = data_test[:, 2]
    t_test_pred = svm.predict(x_test)

    # 评估结果，计算准确率
    acc_train = eval_acc(t_train, t_train_pred)
    acc_test = eval_acc(t_test, t_test_pred)
    print("train accuracy: {:.1f}%".format(acc_train * 100))
    print("test accuracy: {:.1f}%".format(acc_test * 100))
