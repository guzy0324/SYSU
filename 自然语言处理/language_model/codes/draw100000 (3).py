import matplotlib.pyplot as plt

with open('loss/loss_3000_128_128_0.01.txt') as f:
    loss = [float(l) for l in f.readlines()]
plt.plot(range(len(loss)), loss)

with open('loss/loss_100000_128_128_0.01.txt') as f:
    loss = [float(l) for l in f.readlines()]
plt.plot(range(len(loss)), loss)

with open('loss/loss_100000_128_128_0.005.txt') as f:
    loss = [float(l) for l in f.readlines()]
plt.plot(range(len(loss)), loss)

plt.legend(['3000 sentences, LR=0.01', '100000 sentences, LR=0.01', '100000 sentences, LR=0.005'])
plt.xlabel('Epoch')
plt.ylabel('Loss')
plt.show()
