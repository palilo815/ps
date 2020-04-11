import sys
input = sys.stdin.readline

N = int(input())
dots = [[] for i in range(N)]
for i in range(N):
    pos, colour = map(int, input().split())
    dots[colour - 1].append(pos)

ans = 0
for arr in dots:
    L = len(arr)
    if L < 2:
        continue
    arr.sort()
    for i in range(1, L - 1):
        ans += min(arr[i] - arr[i - 1], arr[i + 1] - arr[i])
    ans += arr[L - 1] + arr[1] - arr[L - 2] - arr[0]
print(ans)
