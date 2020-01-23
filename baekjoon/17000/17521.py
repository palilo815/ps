day, money = map(int, input().split())
price = []
coin = 0
for _ in range(day):
    price.append(int(input()))

# 마지막 날에 전부 다 팔게 하기 위함
price.append(-1)
for i in range(day):
    # 가진 코인을 다 판다.
    money += coin * price[i]
    coin = 0

    # 내일 가격이 오르면 다 산다.
    if price[i] < price[i + 1]:
        coin = money // price[i]
        money -= coin * price[i]
print(money)
