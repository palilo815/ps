n = int(input())
ans = 0
while n > 0:
    if n % 5 == 0:
        ans += n // 5
        n = 0
    else:
        ans += 1
        n -= 2
if n < 0:
    ans = -1
print(ans)
