import sys
input = sys.stdin.readline

N, M = map(int, input().split())
wok = list(map(int, input().split()))

cook = set()
for i in range(len(wok)):
    cook.add(wok[i])
    for j in range(i + 1, len(wok)):
        cook.add(wok[i] + wok[j])

DP = [-1] * (N + 1)
DP[0] = 0
for w in cook:
    for i in range(N - w + 1):
        if DP[i] != -1 and (DP[i + w] == -1 or DP[i + w] > DP[i] + 1):
            DP[i + w] = DP[i] + 1

print(DP[N])
