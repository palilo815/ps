import sys
input = sys.stdin.readline

def is_pass(t):
    num = 0
    for x in gate:
        num += t // x
    if num < M:
        return False
    return True


N, M = map(int, input().split())
gate = []
for _ in range(N):
    gate.append(int(input()))

s, e = 1, pow(10, 18)
ans = 0
while s <= e:
    m = s + (e - s) // 2
    if is_pass(m):
        ans = m
        e = m - 1
    else:
        s = m + 1
print(ans)
