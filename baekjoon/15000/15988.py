MOD = 1000000009
DP = [0] * 1000004
DP[0] = 1
for i in range(1000001):
    DP[i] %= MOD
    for j in range(1, 4):
        DP[i + j] += DP[i]
T = int(input())
for t in range(T):
    print(DP[int(input())])
