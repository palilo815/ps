N, mod = map(int, input().split())
arr = map(int, input().split())
ans = 1
for x in arr:
    ans = ans * x % mod
print(ans)
