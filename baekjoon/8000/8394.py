n = int(input())
ans = [1, 1, 0]
num = 2
for i in range(2, n + 1):
    idx = i % 3
    num -= ans[idx]
    ans[idx] = num % 10
    num += ans[idx]
print(ans[n % 3])
