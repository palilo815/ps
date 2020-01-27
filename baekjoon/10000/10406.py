w, n, p = map(int, input().split())
arr = input().split()
ans = 0
for x in arr:
    x = int(x)
    if w <= x <= n:
        ans += 1
print(ans)
