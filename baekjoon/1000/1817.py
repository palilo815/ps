input = __import__('sys').stdin.readline

N, M = map(int, input().split())
book = list(map(int, input().split()))

ans, m = 0, 0
for w in book:
    if w + m > M:
        m = 0
        ans += 1
    m += w
if m:
    ans += 1
print(ans)
