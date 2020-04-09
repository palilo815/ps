import sys
input = sys.stdin.readline

N, K, B = map(int, input().split())
broken = [0] * N
while B:
    B -= 1
    broken[int(input()) - 1] = 1

cnt = 0
for i in range(K):
    if broken[i]:
        cnt += 1

ans = cnt
i, j = 0, K
while j < N:
    cnt += broken[j] - broken[i]
    ans = min(ans, cnt)
    i += 1
    j += 1
print(ans)
