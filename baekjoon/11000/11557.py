T = int(input())
for _ in range(T):
    N = int(input())
    max_drink = 0
    for __ in range(N):
        s, n = input().split()
        if int(n) > max_drink:
            max_drink = int(n)
            max_univ = s
    print(max_univ)
