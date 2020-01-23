s = input()
ans, stick, i = 0, 0, 0
while i < len(s):
    # 레이저 : 밑에 깔린 막대 전부 자른다.
    if s[i] == '(' and s[i + 1] == ')':
        ans += stick
        i += 1
    # 깔린 막대를 하나 추가
    elif s[i] == '(':
        stick += 1
    # 깔린 막대를 없애고 ans 1 추가
    else:
        ans += 1
        stick -= 1
    i += 1
print(ans)
