import numpy as np
import torch
import torch.nn as nn
import torch.optim as optim
from torch.nn.utils.rnn import pack_padded_sequence, pad_packed_sequence
from tqdm import tqdm


SEED = 1
START_TAG, END_TAG = "<s>", "<e>"
GPU = True
LR = 0.01
MAX_EPOCH = 128
BATCH_SIZE = 128
EMBEDDING_DIM = 128
HIDDEN_DIM = 128
SHUFFLE = True


torch.manual_seed(SEED)
torch.cuda.manual_seed(SEED)
np.random.seed(SEED)


class BiLSTM_CRF(nn.Module):
    @staticmethod
    def log_sum_exp(smat_batch):
        vmax_batch = smat_batch.max(dim=1, keepdim=True).values
        return (smat_batch - vmax_batch).exp().sum(axis=1, keepdim=True).log() + vmax_batch

    def __init__(self, ix2tag, word2ix, embedding_dim, hidden_dim, batch_size, device):
        super(BiLSTM_CRF, self).__init__()
        assert hidden_dim % 2 == 0, 'hidden_dim must be even for Bi-Directional LSTM'
        self.embedding_dim, self.hidden_dim = embedding_dim, hidden_dim
        self.ix2tag, self.word2ix, self.n_tags = ix2tag, word2ix, len(ix2tag)
        self.tag2ix = {ix2tag[i]: i for i in range(len(ix2tag))}
        self.batch_size = batch_size
        self.device = device

        self.word_embeds = nn.Embedding(len(word2ix), embedding_dim)
        self.lstm = nn.LSTM(embedding_dim, hidden_dim // 2, num_layers=1, bidirectional=True, batch_first = True)
        self.hidden2tag = nn.Linear(hidden_dim, self.n_tags)
        self.transitions = nn.Parameter(torch.randn(self.n_tags, self.n_tags))
        self.transitions.data[:, self.tag2ix[START_TAG]] = self.transitions.data[self.tag2ix[END_TAG], :] = -10000

    def neg_log_likelihood(self, words_batch, tags_batch):
        frames_batch = self._get_lstm_features(words_batch)
        gold_score_batch = self._score_sentence(frames_batch, tags_batch)
        forward_score_batch = self._forward_alg(frames_batch)
        return (forward_score_batch - gold_score_batch).sum(0) / self.batch_size

    def _get_lstm_features(self, words_batch):
        embeds_batch = self.word_embeds(self._to_tensor(words_batch, self.word2ix)).to(self.device)
        hidden_batch = torch.randn(2, self.batch_size, self.hidden_dim // 2).to(self.device),\
                torch.randn(2, self.batch_size, self.hidden_dim // 2).to(self.device)
        embeds_batch_packed = pack_padded_sequence(embeds_batch, [len(s) for s in words_batch], batch_first = True, enforce_sorted = False)
        lstm_out_batch_packed = self.lstm(embeds_batch_packed, hidden_batch)[0]
        lstm_out_batch = pad_packed_sequence(lstm_out_batch_packed, batch_first = True)[0]
        return self.hidden2tag(lstm_out_batch)

    def _score_sentence(self, frames_batch, tags_batch):
        tags_batch_tensor = self._to_tensor([[START_TAG] + tags for tags in tags_batch], self.tag2ix)
        score_batch = torch.zeros(self.batch_size, 1).to(self.device)
        for i in range(frames_batch.shape[1]):
            score_batch += self.transitions[tags_batch_tensor[:, i], tags_batch_tensor[:, i + 1]].unsqueeze(1) + frames_batch[range(self.batch_size), i, [tags_batch_tensor[j, i + 1] for j in range(self.batch_size)]].unsqueeze(1)
        return score_batch + self.transitions[tags_batch_tensor[:, -1], self.tag2ix[END_TAG]].unsqueeze(1)

    def _forward_alg(self, frames_batch):
        alpha_batch = torch.full((self.batch_size, 1, self.n_tags), -10000).to(self.device)
        alpha_batch[:, 0, self.tag2ix[START_TAG]] = 0
        for i in range(frames_batch.shape[1]):
            alpha_batch = BiLSTM_CRF.log_sum_exp(alpha_batch.transpose(1, 2) + frames_batch[:, i].unsqueeze(1) + self.transitions)
        return BiLSTM_CRF.log_sum_exp(alpha_batch.transpose(1, 2) + 0 + self.transitions[:, [self.tag2ix[END_TAG]]]).squeeze(1)

    def _viterbi_decode(self, frames):
        backtrace = list()
        alpha = torch.full((1, self.n_tags), -10000).to(self.device)
        alpha[0, self.tag2ix[START_TAG]] = 0
        for frame in frames:
            smat = alpha.T + frame.unsqueeze(0) + self.transitions
            backtrace.append(smat.argmax(0))
            alpha = smat.max(dim = 0)[0].unsqueeze(0)
        smat = alpha.T + 0 + self.transitions[:, [self.tag2ix[END_TAG]]]
        best_tag_id = smat.squeeze().argmax().item()
        best_path = [best_tag_id]
        for bptrs_t in reversed(backtrace[1:]):
            best_tag_id = bptrs_t[best_tag_id].item()
            best_path.append(best_tag_id)
        best_path = [self.ix2tag[ix] for ix in best_path[::-1]]
        return smat.max().item(), best_path

    def forward(self, words):
        lstm_feats = self._get_lstm_features([words]).squeeze(0)
        return self._viterbi_decode(lstm_feats)

    def _to_tensor(self, batch, to_ix):
        max_len = max([len(item) for item in batch])
        return torch.tensor([[0 if i >= len(item) else to_ix[item[i]] for i in range(max_len)] for item in batch], dtype=torch.long).to(self.device)


if __name__ == "__main__":
    import os
    import shutil
    if os.path.exists('model'):
        shutil.rmtree('model')
    os.mkdir('model')
    open('F1.txt', 'w')
    device = torch.device("cuda" if GPU and torch.cuda.is_available() else "cpu")
    training_data = list()
    word2ix = dict()
    with open('msrseg/msr_training.utf8', encoding = 'utf8') as f:
        while True:
            line = f.readline()
            if not line:
                break
            sentence = line.split()
            if not sentence:
                continue
            tags = list()
            for word in sentence:
                for ch in word:
                    if ch not in word2ix:
                        word2ix[ch] = len(word2ix)
                if len(word) == 1:
                    tags.append('S')
                else:
                    tags.append('B')
                    for j in range(1, len(word) - 1):
                        tags.append('M')
                    tags.append('E')
            training_data.append((list(''.join(sentence)), tags))
    with open('msrseg/msr_test_gold.utf8', encoding = 'utf8') as f:
        while True:
            line = f.readline()
            if not line:
                break
            sentence = line.split()
            if not sentence:
                continue
            for word in sentence:
                for ch in word:
                    if ch not in word2ix:
                        word2ix[ch] = len(word2ix)
    with open('msrseg/msr_test.utf8', encoding = 'utf8') as f:
        while True:
            line = f.readline()
            if not line:
                break
            sentence = line.split()
            if not sentence:
                continue
            for word in sentence:
                for ch in word:
                    if ch not in word2ix:
                        word2ix[ch] = len(word2ix)

    model = BiLSTM_CRF(ix2tag = [START_TAG, END_TAG, "B", "M", "E", "S"], word2ix = word2ix,
            embedding_dim = EMBEDDING_DIM, hidden_dim = HIDDEN_DIM,
            batch_size = BATCH_SIZE, device = device).to(device)

    optimizer = optim.Adam(model.parameters(), lr=LR, betas=(0.9,0.99))
    words_batch = list()
    tags_batch = list()
    for epoch in range(MAX_EPOCH):
        if SHUFFLE:
            np.random.shuffle(training_data)
        for words, tags in tqdm(training_data, desc = 'Epoch' + str(epoch)):
            words_batch.append(words)
            tags_batch.append(tags)
            if len(words_batch) == BATCH_SIZE or words is training_data[-1][0]:
                model.batch_size = len(words_batch)
                model.zero_grad()
                model.neg_log_likelihood(words_batch, tags_batch).backward()
                optimizer.step()
                words_batch = list()
                tags_batch = list()
        torch.save(model.state_dict(), 'model/' + str(epoch))
