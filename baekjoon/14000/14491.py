n = int(input())
ans = []
while n:
    ans.append(n % 9)
    n //= 9
for i in range(len(ans) - 1, -1, -1):
    print(ans[i], end='')
