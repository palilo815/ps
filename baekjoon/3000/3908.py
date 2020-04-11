import sys
input = sys.stdin.readline

def solve(p):
    for i in range(1120 - p, -1, -1):
        for j in range(1, 14):
            if DP[i][j]:
                DP[i + p][j + 1] += DP[i][j]
    DP[p][1] = 1

DP = [[0 for k in range(15)] for n in range(1121)]
sieve = [False] * 1121
p = 2
while p * p < 1121:
    if not sieve[p]:
        for i in range(p * p, 1121, p):
            sieve[i] = True
    p += 1

for p in range(2, 1121):
    if not sieve[p]:
        solve(p)

T = int(input())
while T:
    T -= 1
    N, K = map(int, input().split())
    print(DP[N][K])
