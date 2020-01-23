u, v = map(int, input().split())
gap = v - u
curr, ans = 1, 0
while curr * 2 < gap:
    gap -= curr * 2
    curr += 1
    ans += 2
if gap > curr:
    ans += 1
    gap -= curr
if gap > 0:
    ans += 1
print(ans)
