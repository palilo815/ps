import sys
input = sys.stdin.readline

N = int(input())
mat = []
for i in range(N):
    mat.append(list(map(int, input().split())))

DP = [[[0] * 10 for j in range(N + 1)] for k in range(N + 1)]
for i in range(1, N + 1):
    for j in range(1, N + 1):
        for k in range(1, 10):
            DP[i][j][k] = -DP[i - 1][j - 1][k] + DP[i][j - 1][k] + DP[i - 1][j][k]
        DP[i][j][mat[i - 1][j - 1]] += 1

Q = int(input())
while Q:
    Q -= 1
    x1, y1, x2, y2 = map(int, input().split())
    ans = 0
    for k in range(1, 10):
        if DP[x2][y2][k] + DP[x1 - 1][y1 - 1][k] - DP[x2][y1 - 1][k] - DP[x1 - 1][y2][k]:
            ans += 1
    print(ans)
