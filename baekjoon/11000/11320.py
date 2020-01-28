T = int(input())
for _ in range(T):
    a, b = map(int, input().split())
    print(a * a // b // b)
