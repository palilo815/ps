input()
ans = 0
for _ in range(2):
    scr = input().split()
    for x in scr:
        ans += abs(int(x))
print(ans)
