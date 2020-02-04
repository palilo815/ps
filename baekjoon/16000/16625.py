def gcd(a, b):
    if a == 0:
        return b
    return gcd(b % a, a)


p, q, s = map(int, input().split())
if p * q // gcd(p, q) > s:
    print("no")
else:
    print("yes")
