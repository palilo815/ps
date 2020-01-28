T = int(input())
for _ in range(T):
    cookie, eat = map(int, input().split())
    print((cookie - 1) // eat + 1)
