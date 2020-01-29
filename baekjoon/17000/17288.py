s = input()
ans = 0
cnt = 1
for i in range(1, len(s)):
    if int(s[i - 1]) + 1 == int(s[i]):
        cnt += 1
    else:
        if cnt == 3:
            ans += 1
        cnt = 1
if cnt == 3:
    ans += 1
print(ans)
