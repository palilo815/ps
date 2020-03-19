import sys
input = sys.stdin.readline

N = int(input())
arr = list(map(int, input().split()))
arr.append(100001)
ans = 0
H, cnt = 0, 0
for h in arr:
    if h > H:
        ans = max(cnt, ans)
        cnt = 0
        H = h
    else:
        cnt += 1
print(ans)
