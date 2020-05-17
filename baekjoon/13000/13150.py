ans = ''
a00, a01 = map(int, input().split())
a10, a11 = map(int, input().split())

while 1:
    L, R = a00 + a10, a01 + a11
    if L == 1 and R == 1: break
    if L > R:
        ans += '0'
        a00 -= a01
        a10 -= a11
    else:
        ans += '1'
        a01 -= a00
        a11 -= a10

print(ans[::-1])