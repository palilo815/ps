N, M = input().split()
M = int(M)
if len(N) * int(N) <= M:
    print(N * int(N))
else:
    repeat = M // len(N)
    remained = M - repeat * len(N)
    print(N * repeat + N[:remained])
