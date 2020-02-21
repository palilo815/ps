import sys
input = sys.stdin.readline

N = int(input())
dist = list(map(int, input().split()))
cost = list(map(int, input().split()))

# 기름의 최솟값을 갱신하면서 계속 진행하면 된다.
ans = 0
min_cost = cost[0]
for i in range(0, N - 1):
    min_cost = min(min_cost, cost[i])
    ans += min_cost * dist[i]
print(ans)
