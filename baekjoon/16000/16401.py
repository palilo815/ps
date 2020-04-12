input = __import__('sys').stdin.readline

M, N = map(int, input().split())
arr = list(map(int, input().split()))

l, r = 1, 1000000000
ans = 0
while l <= r:
    m = (l + r) // 2
    cnt = 0
    for x in arr:
        cnt += x // m
    if cnt >= M:
        ans = m
        l = m + 1
    else:
        r = m - 1
print(ans)
