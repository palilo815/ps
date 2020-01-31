input()
a = list(map(int, input().split()))
ans = 0
for i in range(len(a)):
    if a[i] != i + 1:
        ans += 1
print(ans)
