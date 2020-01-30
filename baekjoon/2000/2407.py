n, m = map(int, input().split())
ans = 1
for i in range(m):
    ans *= n
    n -= 1
for i in range(2, m + 1):
    ans //= i
print(ans)
