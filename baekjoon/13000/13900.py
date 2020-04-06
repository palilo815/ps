import sys
input = sys.stdin.readline

N = int(input())
arr = list(map(int, input().split()))
psum = [0]
for num in arr:
    psum.append(psum[-1] + num)
ans = 0
for i in range(N):
    ans += (psum[N] - psum[i + 1]) * arr[i]
print(ans)
