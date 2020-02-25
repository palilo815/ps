import sys
input = sys.stdin.readline

N, M, K = map(int, input().split())
best = [0] * (N + 1)
for _ in range(M):
    arr = list(input().split())
    for i in range(0, 2 * N, 2):
        idx = int(arr[i])
        val = float(arr[i + 1])
        best[idx] = max(best[idx], val)
best.sort(reverse=True)
ans = 0
for i in range(K):
    ans += best[i]
print("%.1f" % ans)
