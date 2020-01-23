N = int(input())
ans = 0
for _ in range(N):
    s = input()
    for i in s:
        if i == 'A':
            ans += 4
        elif i == 'K':
            ans += 3
        elif i == 'Q':
            ans += 2
        elif i == 'J':
            ans += 1
print(ans)
