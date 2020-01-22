N = int(input())
ans = 0
yesterday = input()
today = input()
for i in range(N):
    if yesterday[i] == 'C' and today[i] == 'C':
        ans += 1
print(ans)
