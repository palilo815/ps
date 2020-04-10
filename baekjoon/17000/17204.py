import sys
input = sys.stdin.readline

N, K = map(int, input().split())
adj = [0] * N
visited = [False] * N
for i in range(N):
    adj[i] = int(input())

u, ans = 0, 0
while u != K:
    if visited[u]:
        print(-1)
        sys.exit(0)
    visited[u] = True
    u = adj[u]
    ans += 1
print(ans)