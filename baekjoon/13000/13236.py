N = int(input())
while 1:
    print(N, end=' ')
    if N == 1:
        break
    if N % 2:
        N = 3 * N + 1
    else:
        N //= 2
