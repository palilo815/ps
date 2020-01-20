MOD = 10007
DP = [0] * 1001
DP[1:2] = 1, 2
N = int(input())
for i in range(3, N + 1):
    DP[i] = (DP[i - 1] + DP[i - 2]) % MOD
print(DP[N])
