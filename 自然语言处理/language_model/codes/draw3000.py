import matplotlib.pyplot as plt

with open('loss/loss_3000_128_128_0.5.txt') as f:
    loss = [float(l) for l in f.readlines()]
plt.plot(range(len(loss)), loss)

with open('loss/loss_3000_128_128_0.1.txt') as f:
    loss = [float(l) for l in f.readlines()]
plt.plot(range(len(loss)), loss)

with open('loss/loss_3000_128_128_0.05.txt') as f:
    loss = [float(l) for l in f.readlines()]
plt.plot(range(len(loss)), loss)

with open('loss/loss_3000_128_128_0.01.txt') as f:
    loss = [float(l) for l in f.readlines()]
plt.plot(range(len(loss)), loss)

plt.legend(['LR=0.5', 'LR=0.1', 'LR=0.05', 'LR=0.01'])
plt.xlabel('Epoch')
plt.ylabel('Loss')
plt.show()
