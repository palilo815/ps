DP = [0] * 91
DP[1], DP[2] = 1, 1
N = int(input())
# DP[i-1]에 0을 붙이거나
# DP[i-2]에 01을 붙이면 된다.
for i in range(3, N + 1):
    DP[i] = DP[i - 1] + DP[i - 2]
print(DP[N])
