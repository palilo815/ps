import sys

input = sys.stdin.readline

N, K = map(int, input().split())
h = list(map(int, input().split()))
ans = 1000

for i in range(N):
    curr = h[i]
    if curr - K * i <= 0:
        continue
    cnt = i
    for j in range(i, N):
        if h[j] != curr:
            cnt += 1
        curr += K
    ans = min(ans, cnt)
print(ans)
