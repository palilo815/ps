N = int(input())
DP = [i for i in range(N + 1)]
for i in range(2, N + 1):
    DP[i] = min(DP[i], DP[i - 2] + 1)
for i in range(5, N + 1):
    DP[i] = min(DP[i], DP[i - 5] + 1)
for i in range(7, N + 1):
    DP[i] = min(DP[i], DP[i - 7] + 1)
print(DP[N])
