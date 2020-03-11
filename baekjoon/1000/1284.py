while 1:
    N = input()
    if N == '0':
        break
    ans = 2 + len(N) - 1
    for x in N:
        if x == '0':
            ans += 4
        elif x == '1':
            ans += 2
        else:
            ans += 3
    print(ans)
