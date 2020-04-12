DP = [[0] * 5 for i in range(32769)]
DP[0][0] = 1

for i in range(1, 182):
    for num in range(32769 - i * i):
        for j in range(4):
            DP[num + i * i][j + 1] += DP[num][j]

while 1:
    N = int(input())
    if not N:
        break
    print(sum(DP[N]))
