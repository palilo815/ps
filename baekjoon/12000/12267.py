import sys
input = sys.stdin.readline

def solve(n):
    len = n * n
    global board
    for i in range(0, len, n):
        for j in range(0, len, n):
            check = [0] * (len + 1)
            for y in range(i, i + n):
                for x in range(j, j + n):
                    if board[y][x] <= 0 or board[y][x] > len or check[board[y][x]]:
                        return 0
                    check[board[y][x]] = 1
    for i in range(len):
        check = [0] * (len + 1)
        for j in range(len):
            if board[i][j] <= 0 or board[i][j] > len or check[board[i][j]]:
                return 0
            check[board[i][j]] = 1
    for j in range(len):
        check = [0] * (len + 1)
        for i in range(len):
            if board[i][j] <= 0 or board[i][j] > len or check[board[i][j]]:
                return 0
            check[board[i][j]] = 1
    return 1


s = ["No", "Yes"]
T = int(input())
for t in range(1, T + 1):
    board = []
    N = int(input())
    for i in range(N * N):
        board.append(list(map(int, input().split())))
    ans = solve(N)
    print("Case #%d:" % t, s[ans])
