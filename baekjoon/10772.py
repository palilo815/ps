T = int(input())
ans = 0
for t in range(T):
    n = int(input())
    p = n % 10
    n //= 10
    ans += pow(n, p)
print(ans)
