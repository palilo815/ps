n, k = map(int, input().split())
ans = 1
for i in range(k):
    ans *= n
    n -= 1
for i in range(1, k + 1):
    ans //= i
print(ans)
