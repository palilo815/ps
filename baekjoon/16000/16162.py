import sys
input = sys.stdin.readline

N, a, d = map(int, input().split())
arr = list(map(int, input().split()))

ans = 0
for x in arr:
    if x == a:
        ans += 1
        a += d
print(ans)
