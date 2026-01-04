x, y, p, a, b = map(int, input().split())
p += b * (y - 1)
print((2 * p - (x - 1) * a) * x // 2)
