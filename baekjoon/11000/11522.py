T = int(input())
for _ in range(T):
    num, n = map(int, input().split())
    print(num, n * (n + 1) // 2, n * n, n * (n + 1))
