def gcd(a, b):
    if a == 0:
        return b
    return gcd(b % a, a)

# 그냥 모든 떨어진 거리에 대한 최대공약수를 구해주면 된다
N, src = map(int, input().split())
dist = list(map(int, input().split()))
for i in range(N):
    dist[i] = abs(dist[i] - src)
ans = dist[0]
for i in range(1, N):
    ans = gcd(ans, dist[i])
print(ans)
