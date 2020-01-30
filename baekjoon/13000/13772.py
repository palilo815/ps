one = ['A', 'D', 'O', 'P', 'Q', 'R']
T = int(input())
for _ in range(T):
    ans = 0
    s = input()
    for x in s:
        if x in one:
            ans += 1
        elif x == 'B':
            ans += 2
    print(ans)
