import sys
input = sys.stdin.readline

N = int(input())
s = input()

N *= 3
DP = [True]
medicine = "DBL"

for i in range(1, N + 1):
    tmp = [False] * (i + 1)
    today = medicine[i % 3]
    for j in range(i):
        if DP[j]:
            if s[j] == today:
                tmp[j + 1] = True
            if s[j + N - i] == today:
                tmp[j] = True
    if not any(tmp):
        i -= 1
        break
    DP = tmp
print(i)
