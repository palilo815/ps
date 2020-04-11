while 1:
    n, k = map(int, input().split())
    if not n:
        break
    k = min(k, n - k)
    ans = 1
    for i in range(n - k + 1, n + 1):
        ans *= i
    for i in range(2, k + 1):
        ans //= i
    print(ans)
