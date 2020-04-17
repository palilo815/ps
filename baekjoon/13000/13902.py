input = __import__('sys').stdin.readline

N, M = map(int, input().split())
arr = list(map(int, input().split()))

wok = set(arr)
for i in range(len(arr)):
    for j in range(i):
        wok.add(arr[i] + arr[j])

DP = [10001] * (N + 1)
DP[0] = 0
for w in wok:
    for i in range(N + 1 - w):
        DP[i + w] = min(DP[i + w], DP[i] + 1)
print(-1 if DP[N] == 10001 else DP[N])
