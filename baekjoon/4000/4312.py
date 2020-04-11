while 1:
    N = int(input())
    if not N:
        break
    N -= 1
    i = 0
    print('{', end='')
    while N:
        if N % 2:
            print('', 3 ** i, end='' if N == 1 else ',')
        N //= 2
        i += 1
    print(" }")
