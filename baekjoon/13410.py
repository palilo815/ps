def rev(n):
    ret = 0
    while n:
        ret *= 10
        ret += n % 10
        n //= 10
    return ret


N, K = map(int, input().split())
ans = 0
for i in range(1, K + 1):
    ans = max(ans, rev(N * i))
print(ans)
