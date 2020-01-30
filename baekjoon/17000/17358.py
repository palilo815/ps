mod = 1000000007
ans = 1
N = int(input())
while N:
    ans = ans * (N - 1) % mod
    N -= 2
print(ans)
