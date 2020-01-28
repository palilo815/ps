s = input()
stk, ans = 0, 0
for c in s:
    if c == '(':
        stk += 1
    else:
        if stk == 0:
            ans += 1
        else:
            stk -= 1
print(ans + stk)
