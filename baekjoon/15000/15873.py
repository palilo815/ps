a = int(input())
b = a % 10
a //= 10
if a <= 10:
    print(a + b)
else:
    print(a // 10 + (10 * (a % 10) + b))
