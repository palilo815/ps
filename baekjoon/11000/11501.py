import sys
input = sys.stdin.readline

T = int(input())
while T:
    T -= 1
    N = int(input())
    price = list(map(int, input().split()))
    price.append(0)

    earn, max_p = 0, 0
    for i in range(N - 1, -1, -1):
        if price[i] > max_p:
            max_p = price[i]
        else:
            earn += max_p - price[i]
    print(earn)
