while 1:
    n = int(input())
    if n == 0:
        break
    if n > 5000000:
        n = n * 8 // 10
    elif n > 1000000:
        n = n * 9 // 10
    print(n)
