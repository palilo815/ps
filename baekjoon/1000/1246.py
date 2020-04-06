N, M = map(int, input().split())
price = []
for i in range(M):
    price.append(int(input()))
price.sort(reverse=True)
money, ans = 0, 0
for i in range(min(N, M)):
    tmp = price[i] * (i + 1)
    if tmp >= money:
        money = tmp
        ans = price[i]
print(ans, money)
