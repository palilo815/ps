s = input()
ans, cnt = 0, 0
for c in s:
    if c == 'R':
        cnt += 1
    else:
        cnt -= 1
    if cnt == 4:
        ans += 1
        cnt = 0
    elif cnt == -4:
        cnt = 0
print(ans)
