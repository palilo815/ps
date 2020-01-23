from math import *

a, b = map(int, input().split())
a *= b
for i in range(1, 10):
    print(ceil(a * i / 10), end=" ")
