N, M = map(int, input().split())
for i in range(N):
    a, b, = input().split()
for i in range(M):
    a, b = input().split()
for i in range(N):
    print(i % 3 + 1, end="")
