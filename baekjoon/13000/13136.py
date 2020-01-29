r, c, n = map(int, input().split())
r = (r - 1) // n + 1
c = (c - 1) // n + 1
print(r * c)
