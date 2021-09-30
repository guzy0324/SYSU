from torch import nn
import torch


class SoftMax(nn.Module):
    def __init__(self, k, C, device="CPU"):
        super(SoftMax, self).__init__()
        self.device = torch.device(device)
        self.linear = nn.Linear(k, C).to(device)
        self.softmax = nn.Softmax(dim=1)

    def forward(self, x):
        return self.softmax(self.linear(x))