T = int(input())
for _ in range(T):
    d = list(map(int, input().split()))
    print(d[2] + d[5] + abs(d[0] - d[3]) + abs(d[1] - d[4]))
