a, d, k = map(int, input().split())
k -= a
if k % d:
    print('X')
else:
    ans = k // d + 1
    if ans < 1:
        print('X')
    else:
        print(k // d + 1)
