T = int(input())
for _ in range(T):
    N, M = map(int, input().split())
    if N < 12 or M < 4:
        print(-1)
    else:
        print(11 * M + 4)
