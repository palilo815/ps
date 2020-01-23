T = int(input())
a, b, h, m = 0, 0, 0, 0
ans = [0] * 4
for t in range(T):
    team, time = input().split()
    H, M = map(int, time.split(":"))
    if a > b:
        ans[0] += H - h
        ans[1] += M - m
    elif a < b:
        ans[2] += H - h
        ans[3] += M - m
    if team == "1":
        a += 1
    else:
        b += 1
    h = H
    m = M
if a > b:
    ans[0] += 47 - h
    ans[1] += 60 - m
elif a < b:
    ans[2] += 47 - h
    ans[3] += 60 - m
ans[0] += ans[1] // 60
ans[1] %= 60
ans[2] += ans[3] // 60
ans[3] %= 60
print(str(ans[0]).zfill(2) + ":" + str(ans[1]).zfill(2))
print(str(ans[2]).zfill(2) + ":" + str(ans[3]).zfill(2))
