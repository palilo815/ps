T = int(input())
for t in range(1, T + 1):
    s = input().split()
    print("Case #" + str(t) + ": ", end='')
    for i in range(len(s) - 1, -1, -1):
        print(s[i], end=' ')
    print()
