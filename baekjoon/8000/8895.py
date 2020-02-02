DP = [[[0 for i in range(21)] for j in range(21)] for k in range(21)]
for i in range(1, 21):
    DP[i][i][1] = 1
    DP[i][1][i] = 1
for n in range(3, 21):
    for l in range(1, n):
        for r in range(1, n):
            val = DP[n - 1][l - 1][r] + DP[n - 1][l][r - 1]
            val += (n - 2) * DP[n - 1][l][r]
            DP[n][l][r] = val
for _ in range(int(input())):
    n, l, r = map(int, input().split())
    print(DP[n][l][r])
