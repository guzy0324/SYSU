from bilstm_crf import *

if __name__ == '__main__':
    word2ix = dict()
    with open('msrseg/msr_training.utf8', encoding = 'utf8') as f:
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
    device = torch.device("cuda" if GPU and torch.cuda.is_available() else "cpu")
    model = BiLSTM_CRF(ix2tag = [START_TAG, END_TAG, "B", "M", "E", "S"], word2ix = word2ix,
            embedding_dim = EMBEDDING_DIM, hidden_dim = HIDDEN_DIM,
            batch_size = BATCH_SIZE, device = device).to(device)
    open('F1.txt', 'w')
    for epoch in tqdm(range(68)):
        model.load_state_dict(torch.load('model/' + str(epoch)))
        f1_sum = 0
        f1_num = 0
        with torch.no_grad():
            with open('msrseg/msr_test_gold.utf8', encoding = 'utf8') as f:
                while True:
                    line = f.readline()
                    if not line:
                        break
                    line = line.split()
                    if not line:
                        continue
                    sentence = set()
                    index = 0
                    for word in line:
                        sentence.add((index, index + len(word)))
                        index += len(word)
                    chs = ''.join(line)
                    predict = set()
                    index = 0
                    tags = model(list(chs))[1]
                    while index < len(tags):
                        tag = tags[index]
                        if tag == 'B':
                            length = 1
                            while index + length < len(tags) and tags[index + length - 1] != 'E':
                                length += 1
                        else:
                            length = 1
                        predict.add((index, index + length))
                        index += length
                    A = len(sentence)
                    B = len(predict)
                    AB = len(sentence & predict)
                    if B != 0:
                        precision = AB / B
                        recall = AB / A
                        if precision + recall != 0:
                            f1_sum += 2 * precision * recall / (precision + recall)
                    f1_num += 1
        f1 = f1_sum / f1_num
        with open('F1.txt', 'a') as f:
            f.write('Epoch ' + str(epoch) + ':\tAverage F1 score: ' + str(f1) + '\n')
