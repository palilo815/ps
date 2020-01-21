N, K = map(int, input().split())
coin = []
for _ in range(N):
    coin.append(int(input()))
ans = 0
for val in coin[::-1]:
    ans += K // val
    K %= val
print(ans)
