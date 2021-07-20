from language_model import *


if __name__ == '__main__':
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
    device = torch.device(
        "cuda:1" if GPU and torch.cuda.is_available() else "cpu")
    model = LanguageModel(len(ix2word), EMBEDDING_DIM,
                          HIDDEN_DIM, BATCH_SIZE, device).to(device)
    cross_entropy_loss = nn.CrossEntropyLoss()
    with torch.no_grad():
        for epoch in range(23, 78):
            total = 0
            num = 0
            model.load_state_dict(torch.load('model' + SUFFIX + '/' + str(epoch)))
            for inputs, outputs in tqdm(training_data, desc='Epoch' + str(epoch)):
                inputs_batch = model._to_tensor([inputs])
                outputs_batch = model._to_tensor([outputs])
                hidden_batch = None
                output_batch = model(inputs_batch.to(device), hidden_batch)[0]
                loss = cross_entropy_loss(output_batch.reshape(-1, len(ix2word)),
                                          outputs_batch.to(device).reshape(-1))
                total += loss * len(inputs)
                num += len(inputs)
                inputs_batch = list()
                outputs_batch = list()
            with open('loss/loss'+SUFFIX+'.txt', 'a') as f:
                f.write(str(float(total / num)) + '\n')