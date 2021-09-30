import torch
from RottenTomatoes import *
from SoftMax import *
from tqdm import tqdm
from pandas import DataFrame

seed = 0
N = 3
k = 4096
device = "cpu"
C = 5

if __name__ == '__main__':
    torch.manual_seed(seed)
    test = RottenTomatoes('test.tsv', N, k, device, "vectorizer", False)
    model = SoftMax(k, C, device=device)
    model.load_state_dict(torch.load("SoftMax"))
    res = {"PhraseId": range(156061, 222353), "Sentiment": []}
    with torch.no_grad():
        for input in tqdm(test):
            action = model(input.reshape(1, -1))
            res["Sentiment"].append(action.argmax().item())
    df = DataFrame(res)
    df.to_csv("res.csv", index=False)