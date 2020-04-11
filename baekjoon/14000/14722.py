import sys
input = sys.stdin.readline

N = int(input())
DP = [[0 for i in range(3)] for j in range(N)]
DP[0][0] = 1

for _ in range(N):
    city = list(map(int, input().split()))
    if DP[0][city[0]]:
        DP[0][(city[0] + 1) % 3] = max(DP[0][(city[0] + 1) % 3], DP[0][city[0]] + 1)
    for i in range(1, N):
        for j in range(3):
            DP[i][j] = max(DP[i - 1][j], DP[i][j])
        if DP[i][city[i]]:
            DP[i][(city[i] + 1) % 3] = max(DP[i][(city[i] + 1) % 3], DP[i][city[i]] + 1)

print(max(DP[N - 1]) - 1)
