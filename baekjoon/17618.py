N = int(input())
ans = 0
for i in range(1, N + 1):
    tmp = 0
    n = i
    while n:
        tmp += n % 10
        n //= 10
    if i % tmp == 0:
        ans += 1
print(ans)
