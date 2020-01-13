s = input()
s += '+'
minus = False
ans, curr = 0, 0
for x in s:
    if '0' <= x <= '9':
        curr = curr * 10 + int(x)
    else:
        if minus:
            ans -= curr
        else:
            ans += curr
        curr = 0
        if x == '-':
            minus = True
print(ans)
