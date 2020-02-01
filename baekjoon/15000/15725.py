s = input()
if 'x' in s:
    pos = s.find('x')
    if pos == 0:
        print(1)
    elif pos == 1 and s[0] == '-':
        print(-1)
    else:
        print(int(s[:pos]))
else:
    print(0)
