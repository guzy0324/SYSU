import numpy as np
import torch
import torch.nn as nn
import torch.optim as optim
from torch.nn.utils.rnn import pack_padded_sequence, pad_packed_sequence
from tqdm import tqdm


SEED = 1
START_TAG, END_TAG = "<s>", "<e>"
GPU = True
LR = 0.005
MAX_EPOCH = 128
BATCH_SIZE = 16
EMBEDDING_DIM = 128
HIDDEN_DIM = 128
SHUFFLE = True
SET_SIZE = 100000
TRAINED_EPOCH = -1
SUFFIX = '_100000_128_128_0.005'


torch.manual_seed(SEED)
torch.cuda.manual_seed(SEED)
np.random.seed(SEED)


class LanguageModel(nn.Module):
    def __init__(self, n_words, embedding_dim, hidden_dim, batch_size, device):
        super(LanguageModel, self).__init__()
        self.n_words, self.embedding_dim, self.hidden_dim = n_words, embedding_dim, hidden_dim
        self.batch_size = batch_size
        self.device = device

        self.word_embeds = nn.Embedding(self.n_words, embedding_dim)
        self.lstm = nn.LSTM(embedding_dim, hidden_dim,
                            num_layers=1, batch_first=True)
        self.hidden2words = nn.Linear(hidden_dim, self.n_words)

    def forward(self, words_batch, hidden_batch=None):
        embeds_batch = self.word_embeds(words_batch).to(self.device)
        if hidden_batch is None:
            hidden_batch = torch.randn(1, self.batch_size, self.hidden_dim).to(self.device),\
                torch.randn(1, self.batch_size,
                            self.hidden_dim).to(self.device)
        embeds_batch_packed = pack_padded_sequence(embeds_batch, [len(
            s) for s in words_batch], batch_first=True, enforce_sorted=False)
        lstm_out_batch_packed, hidden_batch = self.lstm(
            embeds_batch_packed, hidden_batch)
        lstm_out_batch = pad_packed_sequence(
            lstm_out_batch_packed, batch_first=True)[0]
        return self.hidden2words(lstm_out_batch), hidden_batch

    def _to_tensor(self, batch):
        max_len = max([len(item) for item in batch])
        return torch.tensor([[0 if i >= len(item) else item[i] for i in range(max_len)] for item in batch], dtype=torch.long)


if __name__ == '__main__':
    import os
    import shutil
    if TRAINED_EPOCH != -1:
        if os.path.exists('model' + SUFFIX):
            shutil.rmtree('model' + SUFFIX)
        os.mkdir('model' + SUFFIX)
    device = torch.device(
        "cuda" if GPU and torch.cuda.is_available() else "cpu")
    training_data = list()
    word2ix = dict()
    ix2word = list()
    with open('resegmenting_result.utf8', encoding='utf8') as f:
        j = 0
        while j < SET_SIZE:
            j += 1
            line = f.readline()
            if not line:
                break
            sentence = line.split()
            if not sentence:
                continue
            sentence.append(END_TAG)
            for i, word in enumerate(sentence):
                if word not in word2ix:
                    word2ix[word] = len(word2ix)
                    ix2word.append(word)
                sentence[i] = word2ix[word]
            training_data.append((sentence[:-1], sentence[1:]))

    model = LanguageModel(len(ix2word), EMBEDDING_DIM,
                          HIDDEN_DIM, BATCH_SIZE, device).to(device)
    cross_entropy_loss = nn.CrossEntropyLoss()
    optimizer = optim.Adam(model.parameters(), lr=LR, betas=(0.9, 0.99))
    inputs_batch = list()
    outputs_batch = list()
    for epoch in range(TRAINED_EPOCH + 1, MAX_EPOCH):
        if SHUFFLE:
            np.random.shuffle(training_data)
        if TRAINED_EPOCH >= 0:
            model.load_state_dict(torch.load('model' + SUFFIX + '/' + str(TRAINED_EPOCH)))
        for inputs, outputs in tqdm(training_data, desc='Epoch' + str(epoch)):
            inputs_batch.append(inputs)
            outputs_batch.append(outputs)
            if len(inputs_batch) == BATCH_SIZE or inputs is training_data[-1][0]:
                model.batch_size = len(inputs_batch)
                model.zero_grad()
                inputs_batch = model._to_tensor(inputs_batch)
                outputs_batch = model._to_tensor(outputs_batch)
                hidden_batch = None
                output_batch = model(inputs_batch.to(device), hidden_batch)[0]
                loss = cross_entropy_loss(output_batch.reshape(-1, len(ix2word)),
                                          outputs_batch.to(device).reshape(-1))
                loss.backward()
                optimizer.step()
                inputs_batch = list()
                outputs_batch = list()
        torch.save(model.state_dict(), 'model' + SUFFIX + '/' + str(epoch))
