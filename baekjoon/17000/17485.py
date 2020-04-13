input = __import__('sys').stdin.readline

row, col = map(int, input().split())
DP = [[0] * 3 for i in range(col)]

for _ in range(row):
    fuel = list(map(int, input().split()))
    tmp = [[fuel[i]] * 3 for i in range(col)]
    tmp[0][0] += min(DP[1][1], DP[1][2])
    tmp[0][1] += DP[0][0]

    for i in range(1, col - 1):
        tmp[i][0] += min(DP[i + 1][1], DP[i + 1][2])
        tmp[i][1] += min(DP[i][0], DP[i][2])
        tmp[i][2] += min(DP[i - 1][0], DP[i - 1][1])

    tmp[col - 1][1] += DP[col - 1][2]
    tmp[col - 1][2] += min(DP[col - 2][0], DP[col - 2][1])

    DP = tmp

ans = min(DP[0][0], DP[0][1], DP[col - 1][1], DP[col - 1][2])
for i in range(1, col - 1):
    for x in DP[i]:
        ans = min(ans, x)
print(ans)
