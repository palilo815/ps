for _ in range(int(input())):
    N = input()
    L = 10 ** len(N)
    N = int(N)
    M = N * N
    if M % L == N:
        print("YES")
    else:
        print("NO")
