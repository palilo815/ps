scr = []
for _ in range(6):
    scr.append(int(input()))
ans = sum(scr)
ans -= min(scr[:4]) + min(scr[4:])
print(ans)
