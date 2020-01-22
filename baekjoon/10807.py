N = int(input())
arr = list(map(int, input().split()))
key = int(input())
ans = 0
for num in arr:
    if num == key:
        ans += 1
print(ans)
