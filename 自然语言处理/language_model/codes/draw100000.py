import matplotlib.pyplot as plt

with open('loss/loss_100000_128_128_0.01.txt') as f:
    loss = [float(l) for l in f.readlines()][:8]
plt.plot(range(len(loss)), loss)

with open('loss/loss_100000_1024_1024_0.01.txt') as f:
    loss = [float(l) for l in f.readlines()][:8]
plt.plot(range(len(loss)), loss)

plt.legend(['EMBEDDING_DIM=128, HIDDEN_DIM=128', 'EMBEDDING_DIM=1024, HIDDEN_DIM=1024'])
plt.xlabel('Epoch')
plt.ylabel('Loss')
plt.show()
