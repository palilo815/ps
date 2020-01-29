price = [0, 500, 800, 1000]
n = input().split()
money = 5000
for x in n:
    money -= price[int(x)]
print(money)
