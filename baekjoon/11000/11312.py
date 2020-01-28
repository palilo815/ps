T = int(input())
for _ in range(T):
    a, b = map(int, input().split())
    L = a // b
    print(L * L)
