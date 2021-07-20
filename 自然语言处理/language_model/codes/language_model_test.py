from language_model import *


if __name__ == '__main__':
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
    device = torch.device(
        "cuda" if GPU and torch.cuda.is_available() else "cpu")
    model = LanguageModel(len(ix2word), EMBEDDING_DIM,
                          HIDDEN_DIM, BATCH_SIZE, device).to(device)
    model.load_state_dict(torch.load('model' + SUFFIX + '/119'))
    with torch.no_grad():
        while True:
            while True:
                word = input('输入一个词：')
                if word in word2ix:
                    word = word2ix[word]
                    break
                print('词不存在！')
            output = None
            hidden = None
            i = 0
            while ix2word[word] != END_TAG and i < 40:
                print(ix2word[word], end='')
                output, hidden = model(
                    model._to_tensor([[word]]).to(device), hidden)
                word = output.argmax()
                i += 1
            print()
