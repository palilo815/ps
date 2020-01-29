N = int(input())
anj = False
ans = "뭐야"
for _ in range(N):
    name = input()
    if name == "anj":
        anj = True
        break
if anj:
    ans += ';'
else:
    ans += '?'
print(ans)
