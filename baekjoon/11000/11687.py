def solve(n):
    i, ret = 5, 0
    while i <= n:
        ret += n // i
        i *= 5
    return ret


M = int(input())
ans = -1
l, r = 1, 100000000
while l <= r:
    m = (l + r) >> 1
    n = 5 * m
    cnt = solve(n)
    if cnt <= M:
        if cnt == M:
            ans = n
            break
        l = m + 1
    else:
        r = m - 1
print(ans)
