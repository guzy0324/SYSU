from hashlib import md5
import matplotlib.pyplot as plt


domain = 10
sample = 1000000


y = [0] * domain
for i in range(sample):
    y[int(md5(i.to_bytes(64, "little")).hexdigest(), 16) % domain] += 1
plt.bar(range(domain), y)
plt.show()
