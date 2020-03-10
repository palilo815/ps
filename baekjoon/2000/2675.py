for t in range(int(input())):
    r, s = input().split()
    r = int(r)
    for c in s:
        print(c * r, end='')
    print()
