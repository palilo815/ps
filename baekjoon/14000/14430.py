import sys
input = sys.stdin.readline

row, col = map(int, input().split())
board = []
for i in range(row):
    board.append(list(map(int, input().split())))
DP = [[0 for j in range(col + 1)] for i in range(row + 1)]
for r in range(1, row + 1):
    for c in range(1, col + 1):
        DP[r][c] = max(DP[r - 1][c], DP[r][c - 1])
        if board[r - 1][c - 1]:
            DP[r][c] += 1
print(DP[row][col])
