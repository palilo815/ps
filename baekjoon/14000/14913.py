a, d, k = map(int, input().split())
k -= a
if k % d:
    print('X')
else:
    print(k // d + 1)
