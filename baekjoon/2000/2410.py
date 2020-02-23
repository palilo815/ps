mod = 1000000000
N = int(input())
DP = [1 for i in range(N + 1)]
x = 2
while x <= N:
    for i in range(x, N + 1):
        DP[i] = (DP[i] + DP[i - x]) % mod
    x *= 2
print(DP[N])
