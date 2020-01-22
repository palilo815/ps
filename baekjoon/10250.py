T = int(input())
for _ in range(T):
    r, c, n = map(int, input().split())
    num = n // r + 1
    floor = n % r
    print(floor * 100 + num)
