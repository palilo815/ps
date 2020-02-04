c, k, p = map(int, input().split())
wine = 0
for i in range(1, c + 1):
    wine += k * i + p * i * i
print(wine)
