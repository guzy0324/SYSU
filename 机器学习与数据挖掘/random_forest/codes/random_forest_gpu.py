import torch
import numpy as np
import pandas as pd
from tqdm import tqdm

def NEG_B(q):
    I_q = 1 - q
    return q.xlogy(q) + I_q.xlogy(I_q)

def NEG_REMAINDER_MUL_N(S, F):
    label = S[:, -1:]
    S1 = S[:, F]

    p1 = (S1 * label).sum(dim=0)
    N1 = S1.sum(dim=0)

    p0 = label.sum() - p1
    N0 = S.shape[0] - N1

    return N1 * NEG_B(p1 / N1) + N0 * NEG_B(p0 / N0)

def read(path, IMPORTANCE, device='cpu'):
    device = torch.device(device)
    dataset = pd.read_csv(path)
    XY_list = list()
    threshold_list = list()
    F = range(dataset.shape[1] - 5)
    for i in range(4):
        Y = torch.tensor(np.array(dataset.iloc[1:, i + 1:i + 2]), dtype=torch.float32, device=device, requires_grad=False)
        X = torch.tensor(np.array(dataset.iloc[1:, 5:]), dtype=torch.float32, device=device, requires_grad=False)
        threshold = torch.zeros(len(F), device=device, requires_grad=False)
        for f in tqdm(F):
            mids = X[:, f]
            mids.sort()
            mids = ((mids[:-1] + mids[1:]) / 2).unique()

            x_best = None
            mid_best = None
            score_best = -float("inf")
            for mid in mids:
                x = X[:, f:f + 1] >= mid
                score = IMPORTANCE(torch.cat((x, Y), axis=1), torch.tensor([0], device=device, requires_grad=False))
                if score_best < score:
                    x_best = x
                    mid_best = mid
                    score_best = score
            X[:, f:f + 1] = x_best
            threshold[f] = mid_best
        XY_list.append(torch.cat((X.to(int), Y), axis=1))
        threshold_list.append(threshold)
    return XY_list, threshold_list
