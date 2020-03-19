for _ in range(int(input())):
    s = input()
    a, b = [], []
    i = 0
    while 1:
        if a and a[0] == s[i]:
            break
        a.append(s[i])
        i = (i + 1) % len(s)
        b.append((s[i]))
        i = (i + 1) % len(s)
    for x in a:
        print(x, end='')
    print()
    for x in b:
        print(x, end='')
    print()
