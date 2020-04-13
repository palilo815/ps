input = __import__('sys').stdin.readline

N = int(input())
board = []
for i in range(N):
    board.append(list(map(int, input().split())))
    board[i].append(1)
board.append([1] * (N + 1))

DP = [[[0] * 3 for i in range(N + 1)] for j in range(N + 1)]
DP[0][0][0] = 1

for i in range(N):
    for j in range(N):
        if board[i][j + 1]:
            DP[i][j][0] = 0
        if board[i + 1][j]:
            DP[i][j][1] = 0
        if board[i][j + 1] or board[i + 1][j] or board[i + 1][j + 1]:
            DP[i][j][2] = 0

        DP[i][j + 1][0] += DP[i][j][0]
        DP[i][j + 1][2] += DP[i][j][0]

        DP[i + 1][j][1] += DP[i][j][1]
        DP[i + 1][j][2] += DP[i][j][1]

        DP[i + 1][j + 1][0] += DP[i][j][2]
        DP[i + 1][j + 1][1] += DP[i][j][2]
        DP[i + 1][j + 1][2] += DP[i][j][2]

print(DP[N - 2][N - 2][2] + DP[N - 2][N - 1][1] + DP[N - 1][N - 2][0])
