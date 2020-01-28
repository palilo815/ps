T = int(input())
for _ in range(T):
    b, n, s, p = map(int, input().split())
    P = b + p * n
    S = s * n
    if P < S:
        print("parallelize")
    elif P > S:
        print("do not parallelize")
    else:
        print("does not matter")
