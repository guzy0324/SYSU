from torch.utils.data import Dataset
import pandas
from sklearn.pipeline import Pipeline
from sklearn.feature_extraction.text import CountVectorizer
from sklearn.feature_selection import SelectKBest, chi2
import joblib
import torch


class RottenTomatoes(Dataset):
    def __init__(self, path, N, k, device="cpu", vectorizer=None, train=True):
        df = pandas.read_csv(path, sep="\t")
        if vectorizer == None:
            self.vectorizer = Pipeline([
                ("N-GRAM", CountVectorizer(ngram_range=(1, N))),
                ("chi2", SelectKBest(chi2, k=k))
            ]).fit(df["Phrase"], df["Sentiment"])
            joblib.dump(self.vectorizer, "vectorizer")
        else:
            self.vectorizer = joblib.load(vectorizer)
        self.device = torch.device(device)
        self.phrase = torch.tensor(self.vectorizer.transform(df["Phrase"]).A,
                                   dtype=torch.float32,
                                   device=self.device)
        self.train = train
        if train:
            self.weight = 1.0 / torch.tensor(
                df["Sentiment"].value_counts(sort=False).to_numpy(),
                dtype=torch.float32,
                device=device)
            self.sentiment = torch.tensor(df["Sentiment"].values,
                                          device=self.device)

    def __len__(self):
        return len(self.phrase)

    def __getitem__(self, key):
        if self.train:
            return self.phrase[key], self.sentiment[key]
        return self.phrase[key]