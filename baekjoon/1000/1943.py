import sys
input = sys.stdin.readline

T = 3
while T:
    T -= 1
    N = int(input())
    coin = []
    total = 0
    for i in range(N):
        coin.append(list(map(int, input().split())))
        total += coin[-1][0] * coin[-1][1]

    if total % 2:
        print(0)
        continue

    total //= 2
    DP = [False] * (total + 1)
    DP[0] = True

    for val, cnt in coin:
        for i in range(total, -1, -1):
            if DP[i]:
                for j in range(1, cnt + 1):
                    if i + val * j > total:
                        break
                    DP[i + val * j] = True
    print(1 if DP[total] else 0)
