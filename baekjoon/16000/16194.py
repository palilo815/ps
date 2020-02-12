import sys

input = sys.stdin.readline

N = int(input())
DP = [10000000] * (N + 1)
DP[0] = 0
price = [0]
price.extend(list(map(int, input().split())))
for i in range(1, N + 1):
    for cnt in range(i, N + 1):
        DP[cnt] = min(DP[cnt], DP[cnt - i] + price[i])
print(DP[N])
