def gcd(A, B):
    if A == 0:
        return B
    return gcd(B % A, A)


T = int(input())
for t in range(T):
    a, b = map(int, input().split())
    print(a * b // gcd(a, b))
