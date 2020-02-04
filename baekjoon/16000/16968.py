s = input()
if s[0] == 'c':
    ans = 26
else:
    ans = 10
for i in range(1, len(s)):
    if s[i] == 'c':
        tmp = 26
    else:
        tmp = 10
    if s[i] == s[i - 1]:
        tmp -= 1
    ans *= tmp
print(ans)
