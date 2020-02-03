def gcd(x, y):
    if x == 0:
        return y
    return gcd(y % x, x)


for _ in range(int(input())):
    a, b = map(int, input().split())
    while a > 1:
        tmp = b // a + 1
        a = a * tmp - b
        b *= tmp
        g = gcd(a, b)
        a //= g
        b //= g
    print(b)
