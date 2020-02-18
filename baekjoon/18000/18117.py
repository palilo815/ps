import sys
input = sys.stdin.readline

def pow_10(k, mod):
    if k == 0:
        return 1
    ret = 10 if k % 2 else 1
    half = pow_10(k // 2, mod)
    return (ret * half * half) % mod

# a/b 의 k번째 숫자
# = (a * 10^(k-1) % b * 10) // b

for t in range(int(input())):
    a, b = map(int, input().split())
    i, n = map(int, input().split())
    tmp = (a * pow_10(i - 1, b)) % b
    for _ in range(n):
        tmp *= 10
        print(tmp // b, end="")
        tmp %= b
    print()
