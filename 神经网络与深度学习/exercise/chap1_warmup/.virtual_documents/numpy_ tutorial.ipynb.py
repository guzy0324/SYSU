import numpy as np


a = np.array([4, 5, 6])
print(a.dtype)
print(a[0])


b = np.array([[4, 5, 6], [1, 2, 3]])
print(b.shape)
print(b[0, 0], b[0, 1], b[1, 1])


a = np.zeros((3, 3), dtype=int)
b = np.ones((4, 5), dtype=int)
c = np.eye(4, dtype=int)
d = np.random.rand(3, 2)


a = np.array([[1, 2, 3, 4], [5, 6, 7, 8], [9, 10, 11, 12]])
print(a)
print(a[2, 3], a[0, 0])


b = a[0:2, 2:4]
print(b)
print(b[0, 0])


c = a[-2:, :]
print(a[0, -1])


a = np.array([[1, 2], [3, 4], [5, 6]])
print(a[[0, 1, 2], [0, 1, 0]])


a = np.array([[1, 2, 3], [4, 5, 6], [7, 8, 9], [10, 11, 12]])
b = [0, 2, 0, 1]
print(a[range(4), b])


a[range(4), b] += 10
print(a)


x = np.array([1, 2])
print(x.dtype)


x = np.array([1.0, 2.0])
print(x.dtype)


x = np.array([[1, 2], [3, 4]], dtype=np.float64)
y = np.array([[5, 6], [7, 8]], dtype=np.float64)
print(x + y)
print(np.add(x, y))


print(x - y)
print(np.subtract(x, y))


print(x * y)
print(np.multiply(x, y))
print(np.dot(x, y))


print(x / y)
print(np.divide(x, y))


print(x ** 0.5)
print(np.sqrt(x))


print(x.dot(y))
print(np.dot(x, y))


print(np.sum(x))
print(np.sum(x, axis=0))
print(np.sum(x, axis=1))


print(np.mean(x))
print(np.mean(x, axis=0))
print(np.mean(x, axis=1))


x = x.T
print(x)


print(np.exp(x))


print(np.argmax(x))
print(np.argmax(x, axis=0))
print(np.argmax(x, axis=1))


import matplotlib.pyplot as plt

x = np.arange(0, 100, 0.1)
y = x * x
plt.plot(x, y)


x = np.arange(0, 3 * np.pi, 0.1)
plt.plot(x, np.sin(x))
plt.plot(x, np.cos(x))
