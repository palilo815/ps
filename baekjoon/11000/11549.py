ans = 0
n = int(input())
arr = list(map(int, input().split()))
for x in arr:
    if x == n:
        ans += 1
print(ans)
