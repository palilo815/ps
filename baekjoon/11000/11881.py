input = __import__('sys').stdin.readline
MAX = 100001
mod = 1000000007

cnt = [0] * MAX
ans, L, R = 0, 0, 0

input()
arr = list(map(int, input().split()))

for x in arr:
    cnt[x] += 1
    R += x

for i in range(1, MAX):
    M = i * cnt[i]
    R -= M
    ans = (ans + L * M * R) % mod
    L += M

print(ans)
