N = int(input())
DP = [300001] * (N + 1)
DP[0] = 0

l, layer, cnt = 1, 1, 1
while cnt <= N:
    for i in range(N - cnt + 1):
        DP[i + cnt] = min(DP[i] + 1, DP[i + cnt])
    l += 1
    layer += l
    cnt += layer
print(DP[N])
