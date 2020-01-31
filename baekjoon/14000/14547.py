while 1:
    s = input()
    if s == '#':
        break
    s = s.split()[1]
    ans = []
    for i in range(3):
        if s[i] == s[i + 1] and s[i] not in ans:
            ans.append(s[i])
    for i in range(len(ans)):
        if i != 0:
            print(" and", end=' ')
        print(ans[i], ans[i], "glued", end="")
        if i == len(ans) - 1:
            print()
