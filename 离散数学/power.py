import time


def power(x, n, table=dict()):
    if n == 0:
        return 0
    if n == 1:
        return x
    if table.get(int(n / 2)) is None:
        table[int(n / 2)] = power(x, int(n / 2), table)
    if table.get(n - int(n / 2)) is None:
        table[n - int(n / 2)] = power(x, n - int(n / 2), table)
    return table[int(n / 2)] * table[n - int(n / 2)]


def power1(x, n):
    if n == 0:
        return 0
    if n == 1:
        return x
    return power1(x, int(n / 2)) * power1(x, n - int(n / 2))


p = 10000000
s = time.time()
power(2, p)
e = time.time()
print(e - s)
s = time.time()
power1(2, p)
e = time.time()
print(e - s)
