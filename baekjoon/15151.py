k, d = map(int, input().split())
ans = 0
while k <= d:
    d -= k
    k *= 2
    ans += 1
print(ans)
