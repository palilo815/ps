while 1:
    N = int(input())
    if N == 0:
        break
    a, b = 0, 0
    coin = list(map(int, input().split()))
    for x in coin:
        if x == 0:
            a += 1
        else:
            b += 1
    print("Mary won {0} times and John won {1} times".format(a, b))
