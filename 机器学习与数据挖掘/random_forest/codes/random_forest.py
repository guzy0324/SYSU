import numpy as np
import pandas as pd
from scipy.special import xlogy
import json
from tqdm import tqdm
from math import ceil

def NEG_B(q):
    I_q = 1 - q
    return xlogy(q, q) + xlogy(I_q, I_q)

def NEG_REMAINDER_MUL_N(S, F):
    label = S[:, -1:]
    S1 = S[:, F]

    p1 = np.sum(S1 & label)
    N1 = np.sum(S1)

    p0 = np.sum(label) - p1
    N0 = S.shape[0] - N1

    return N1 * NEG_B(p1 / N1) + N0 * NEG_B(p0 / N0)

def NEG_GINI_MINUS_1(p):
    return p ** 2 + (1 - p) ** 2

def NEG_GINI_INDEX_MINUS_1_MUL_N(S, F):
    label = S[:, -1:]
    S1 = S[:, F]

    p1 = np.sum(S1 & label)
    N1 = np.sum(S1)

    p0 = np.sum(label) - p1
    N0 = S.shape[0] - N1

    return N1 * NEG_GINI_MINUS_1(p1 / N1) + N0 * NEG_GINI_MINUS_1(p0 / N0)

def read(path, IMPORTANCE):
    dataset = pd.read_csv(path)
    if type(IMPORTANCE) is str:
        with open(IMPORTANCE) as f:
            threshold_list = json.loads(f.read())
        XY_list = list()
        F = range(dataset.shape[1] - 5)
        for i in range(4):
            X = (np.array(dataset.iloc[1:, 5:]) >= threshold_list[i]).astype(int)
            Y = np.array(dataset.iloc[1:, i + 1:i + 2])
            XY_list.append(np.concatenate((X, Y), axis=1))
    else:
        XY_list = list()
        threshold_list = list()
        F = range(dataset.shape[1] - 5)
        for i in range(4):
            Y = np.array(dataset.iloc[1:, i + 1:i + 2])
            X = np.array(dataset.iloc[1:, 5:])
            threshold = np.zeros(len(F))
            for f in tqdm(F):
                mids = X[:, f]
                np.sort(mids)
                mids = np.unique(mids)
                mids = (mids[:-1] + mids[1:]) / 2

                x_best = None
                mid_best = None
                score_best = -float("inf")
                for mid in mids:
                    x = X[:, f:f + 1] >= mid
                    score = IMPORTANCE(np.concatenate((x, Y), axis=1), np.array([0]))
                    if score_best < score:
                        x_best = x
                        mid_best = mid
                        score_best = score
                X[:, f:f + 1] = x_best
                threshold[f] = mid_best
            XY_list.append(np.concatenate((X.astype(int), Y), axis=1))
            threshold_list.append(threshold)
    return XY_list, threshold_list

def save_threshold_list(threshold_list, path):
    with open(path, 'w') as f:
        f.write(str([t.tolist() for t in threshold_list]))

class DecisionTree(object):
    def __init__(self, attribute_name):
        self.attribute_name = attribute_name
        self.branches = dict()

    def add_a_branch(self, vk, subtree):
        self.branches[vk] = subtree

def RandomForest(S, IMPORTANCE, B):
    H = list()
    F = np.array(range(S.shape[1] - 1))
    for _ in range(B):
        rand_order = np.random.choice(np.array(range(len(S))), len(S))
        H.append(RandomizedTreeLearn(S[rand_order, :], F, IMPORTANCE))
    return H

def RandomizedTreeLearn(S, F, IMPORTANCE):
    if S.shape[0] == 0:
        return None
    plurality_value = np.argmax(np.bincount(S[:, -1]))
    if F.shape[0] == 0 or (S[0, -1] == S[:, -1]).all():
        return plurality_value
    f = np.random.choice(F, int(np.log2(len(F))) + 1, replace=False)
    A_idx = np.argmax(IMPORTANCE(S, f))
    A = f[A_idx]
    F = np.delete(F, np.where(F == A))
    tree = DecisionTree(A)

    subtree = RandomizedTreeLearn(S[np.where(S[:, A])[0], :], F, IMPORTANCE)
    if subtree is None:
        subtree = plurality_value
    tree.add_a_branch(1, subtree)

    subtree = RandomizedTreeLearn(S[np.where(S[:, A] == 0)[0], :], F, IMPORTANCE)
    if subtree is None:
        subtree = plurality_value
    tree.add_a_branch(0, subtree)

    return tree

def RandomForestPredict(X, H):
    hist = [0, 0]
    for tree in H:
        hist[DecisionTreePredict(X, tree)] += 1
    return max((0, 1), key=lambda k: hist[k])

def DecisionTreePredict(X, tree):
    if type(tree) is DecisionTree:
        return DecisionTreePredict(X, tree.branches[X[tree.attribute_name]])
    return tree

def test(XY_list, IMPORTANCE, B):
    size = len(XY_list[0])
    rand_order = np.array(range(size))
    np.random.shuffle(rand_order)
    for i in range(4):
        XY_list[i] = XY_list[i][rand_order, :]
    counts_sep = [[0, 0, 0, 0],
                [0, 0, 0, 0],
                [0, 0, 0, 0],
                [0, 0, 0, 0],
                [0, 0, 0, 0]]
    counts = [0, 0, 0, 0, 0]
    tot = [0, 0, 0, 0, 0]
    with tqdm(total=5 * 4) as pbar:
        size = ceil(size / 5)
        for i in range(5):
            out = list()
            for j in range(4):
                S = XY_list[j]
                S_t = np.concatenate((S[:i*size, :], S[(i+1)*size:, :]), axis=0)
                S_v = S[i*size:(i+1)*size, :]
                tot[i] = S_v.shape[0]
                H = RandomForest(S_t, IMPORTANCE, B)
                for k, XY in enumerate(S_v):
                    is_right = XY[-1] == RandomForestPredict(XY[:-1], H)
                    counts_sep[i][j] += is_right
                    if j == 0:
                        out.append(is_right)
                    else:
                        out[k] &= is_right
                pbar.update(1)
            counts[i] = sum(out)
        return counts, counts_sep, tot
