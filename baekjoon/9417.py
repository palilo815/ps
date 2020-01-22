def gcd(a, b):
    if a == 0:
        return b
    return gcd(b % a, a)


T = int(input())
for t in range(T):
    ans = 0
    num = list(map(int, input().split()))
    for i in range(len(num)):
        for j in range(i + 1, len(num)):
            ans = max(ans, gcd(num[i], num[j]))
    print(ans)
