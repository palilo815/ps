while 1:
    B, N = map(int, input().split())
    if B == 0:
        break
    A = 1
    while A ** N < B:
        A += 1
    if A ** N - B > B - (A - 1) ** N:
        A -= 1
    print(A)
