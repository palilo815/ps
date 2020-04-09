import sys
input = sys.stdin.readline

N, K = map(int, input().split())
h = list(map(int, input().split()))
ans = 0
for i in range(N):
    curr = h[i]
    for j in range(i, N):
        if h[j] == curr:
            curr += K
    ans = max(ans, (curr - h[i]) // K)
print(N - ans)
