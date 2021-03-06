from bilstm_crf import *


def init_word2ix(word2ix, path):
    with open(path, encoding = 'utf8') as f:
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


def resegment(f1, path, model):
    with open(path, encoding = 'utf8') as f:
        while True:
            raw_line = f.readline()
            if not raw_line:
                break
            line = raw_line.split()
            if not line:
                f1.write(raw_line)
                continue
            line = ''.join(line)
            tags = model(list(line))[1]
            index = 0
            while index < len(tags):
                tag = tags[index]
                if tag == 'B':
                    length = 1
                    while index + length < len(tags) and tags[index + length - 1] != 'E':
                        length += 1
                else:
                    length = 1
                f1.write(line[index:index + length])
                f1.write(' ')
                index += length
            f1.write('\n')


if __name__ == '__main__':
    word2ix = dict()
    init_word2ix(word2ix, 'msrseg/msr_training.utf8')
    init_word2ix(word2ix, 'msrseg/msr_test_gold.utf8')
    init_word2ix(word2ix, 'msrseg/msr_test.utf8')
    device = torch.device("cuda" if GPU and torch.cuda.is_available() else "cpu")
    model = BiLSTM_CRF(ix2tag = [START_TAG, END_TAG, "B", "M", "E", "S"], word2ix = word2ix,
            embedding_dim = EMBEDDING_DIM, hidden_dim = HIDDEN_DIM,
            batch_size = BATCH_SIZE, device = device).to(device)
    model.load_state_dict(torch.load('65'))
    with torch.no_grad():
        with open('resegmenting_result.utf8', 'w' ,encoding = 'utf8') as f1:
            resegment(f1, 'msrseg/msr_training.utf8', model)
            resegment(f1, 'msrseg/msr_test_gold.utf8', model)
            resegment(f1, 'msrseg/msr_test.utf8', model)
