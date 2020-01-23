T = int(input())
for _ in range(T):
    r, c, n = map(int, input().split())
    num = (n - 1) // r + 1
    floor = (n - 1) % r + 1
    print(floor * 100 + num)
