def hansu(a):
    c = a % 10
    a //= 10
    b = a % 10
    a //= 10
    return a - b == b - c


N = int(input())
ans = min(N, 99)
for n in range(100, N + 1):
    if (hansu(n)):
        ans += 1
print(ans)
