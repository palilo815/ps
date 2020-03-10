DP = [[0, 0] for _ in range(41)]
DP[0] = [1, 0]
DP[1] = [0, 1]
for i in range(2, 41):
    DP[i][0] = DP[i - 2][0] + DP[i - 1][0]
    DP[i][1] = DP[i - 2][1] + DP[i - 1][1]
for i in range(int(input())):
    n = int(input())
    print(DP[n][0], DP[n][1])
