limit = [0] * 100
speed = [0] * 100
N, M = map(int, input().split())
i = 0
for _ in range(N):
    d, v = map(int, input().split())
    for j in range(d):
        limit[i] = v
        i += 1
i = 0
for _ in range(M):
    d, v = map(int, input().split())
    for j in range(d):
        speed[i] = v
        i += 1
ans = 0
for i in range(100):
    ans = max(ans, speed[i] - limit[i])
print(ans)
