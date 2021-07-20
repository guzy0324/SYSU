import matplotlib.pyplot as plt

with open('loss/loss_100000_128_128_0.01.txt') as f:
    loss = [float(l) for l in f.readlines()][:4]
plt.plot(range(len(loss)), loss)

with open('loss/loss_100000_128_128_0.005.txt') as f:
    loss = [float(l) for l in f.readlines()][:4]
plt.plot(range(len(loss)), loss)

with open('loss/loss_100000_128_128_0.001.txt') as f:
    loss = [float(l) for l in f.readlines()]
plt.plot(range(len(loss)), loss)

plt.legend(['LR=0.01', 'LR=0.005', 'LR=0.001'])
plt.xlabel('Epoch')
plt.ylabel('Loss')
plt.show()
