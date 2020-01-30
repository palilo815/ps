def gcd(a, b):
    if a == 0:
        return b
    return gcd(b % a, a)


A, B = map(int, input().split())
print(A * B // gcd(A, B))
