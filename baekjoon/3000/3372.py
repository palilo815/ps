import sys
input = sys.stdin.readline

N = int(input())
DP = [[0 for i in range(N)] for j in range(N)]
DP[0][0] = 1
board = []
for i in range(N):
    board.append(list(map(int, input().split())))
for i in range(N):
    for j in range(N):
        jump = board[i][j]
        if jump == 0:
            continue
        if i + jump < N:
            DP[i + jump][j] += DP[i][j]
        if j + jump < N:
            DP[i][j + jump] += DP[i][j]
print(DP[N - 1][N - 1])
