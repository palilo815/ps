import sys
input = sys.stdin.readline

N, K = map(int, input().split())
arr = list(map(int, input().split()))

cnt = []
for i in range(K):
    tmp = [0, 0]
    for j in range(i, N, K):
        tmp[arr[j] % 2] += 1
    cnt.append(tmp)

change = [0] * K
gap, idx, _sum, ans = 1e6, 0, 0, 0
for i in range(K):
    ans += min(cnt[i])
    if cnt[i][1] > cnt[i][0]:
        change[i] = 1
        _sum += 1
    if abs(cnt[i][0] - cnt[i][1]) < gap:
        gap = abs(cnt[i][0] - cnt[i][1])
        idx = i

if _sum % 2:
    change[idx] = 1 - change[idx]
    ans += abs(cnt[idx][0] - cnt[idx][1])

print(ans)
for i in range(N):
    if arr[i] % 2 != change[i % K]:
        arr[i] = change[i % K]
    print(arr[i], end=' ')
