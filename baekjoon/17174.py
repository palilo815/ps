N, M = map(int, input().split())
ans = 0
while N > 0:
    ans += N
    N //= M
print(ans)
