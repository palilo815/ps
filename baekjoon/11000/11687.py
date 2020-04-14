def solve(n):
    i, ret = 5, 0
    while i <= n:
        ret += n // i
        i *= 5
    return ret


M = int(input())
ans = 5 * M
while True:
    cnt = solve(ans)
    if cnt <= M:
        break
    ans -= 5
print(ans if cnt == M else -1)
