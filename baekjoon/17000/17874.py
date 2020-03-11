n, h, v = map(int, input().split())
h = max(h, n - h)
v = max(v, n - v)
print(h * v * 4)
