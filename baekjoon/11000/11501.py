import sys
input = sys.stdin.readline

T = int(input())
while T:
    T -= 1
    N = int(input())
    price = list(map(int, input().split()))
    price.append(0)

    stock, earn = 0, 0
    for i in range(N):
        if price[i] < price[i + 1]:
            stock += 1
            earn -= price[i]
        else:
            earn += stock * price[i]
            stock = 0
    print(earn)
