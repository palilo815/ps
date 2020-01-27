DP = [0] * 11
DP[1:3] = 1, 2, 4
for i in range(4, 11):
    DP[i] = DP[i - 1] + DP[i - 2] + DP[i - 3]
T = int(input())
for t in range(T):
    N = int(input())
    print(DP[N])
