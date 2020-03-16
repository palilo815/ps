while 1:
    a, d, s = map(int, input().split())
    if d == 0:
        break
    gap = s - a
    ans = gap // d + 1
    if gap % d or ans < 1:
        print('X')
    else:
        print(ans)
