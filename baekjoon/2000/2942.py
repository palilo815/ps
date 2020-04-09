import math

R, G = map(int, input().split())
gcd = math.gcd(R, G)
i = 1
while i * i < gcd:
    if gcd % i == 0:
        print(i, R // i, G // i)
        print(gcd // i, R // (gcd // i), G // (gcd // i))
    i += 1
if i * i == gcd:
    print(i, R // i, G // i)
