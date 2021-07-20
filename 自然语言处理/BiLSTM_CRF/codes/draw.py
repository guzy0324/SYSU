import re
import matplotlib.pyplot as plt
epoch = list()
f1 = list()
with open('F1.txt') as f:
    while True:
        line = f.readline()
        if not line:
            break
        temp = re.findall(r'[0-9]+\.*[0-9]*', line)
        epoch.append(int(temp[0]))
        f1.append(float(temp[-1]))
plt.xlabel('Epoch')
plt.ylabel('Average F1 score')
plt.scatter(epoch, f1)
plt.show()