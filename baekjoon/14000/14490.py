def gcd(a, b):
    if a == 0:
        return b
    return gcd(b % a, a)


n, m = map(int, input().split(':'))
g = gcd(n, m)
print(str(n // g) + ':' + str(m // g))
