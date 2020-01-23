T = int(input())
for _ in range(T):
    N = int(input())
    price = 0
    name = ""
    for i in range(N):
        a, b = input().split()
        if int(a) > price:
            price = int(a)
            name = b
    print(name)
