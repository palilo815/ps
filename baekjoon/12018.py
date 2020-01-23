N, M = map(int, input().split())
need = []
for _ in range(N):
    P, L = map(int, input().split())
    point = list(map(int, input().split()))
    if P < L:
        need.append(1)
    else:
        point.sort(reverse=True)
        need.append(point[L - 1])
need.sort()
ans = 0
for i in need:
    if M - i < 0:
        break
    ans += 1
    M -= i
print(ans)
