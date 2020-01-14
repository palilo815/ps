def hanoi(num, u, v):
    if num == 1:
        print(u, v)
    else:
        hanoi(num - 1, u, 6 - u - v)
        print(u, v)
        hanoi(num - 1, 6 - u - v, v)


n = int(input())
print(2 ** n - 1)
if n <= 20:
    hanoi(n, 1, 3)
