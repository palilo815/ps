import sys

input = sys.stdin.readline

N = int(input())
a, b, c = 0, 0, 0
for i in range(N):
    piece = input()
    if piece[2] == '2':
        b += 1
    elif piece[0] == '1':
        a += 1
    else:
        c += 1

ans = c
a -= c
ans += (b + 1) // 2
if b % 2:
    a -= 2
if a > 0:
    ans += (a + 3) // 4
print(ans)
