x, y, m = map(int, input().split())
ans = 0
i = 0
while x * i <= m:
    j = 0
    while x * i + y * j <= m:
        ans = max(ans, x * i + y * j)
        j += 1
    i += 1
print(ans)
