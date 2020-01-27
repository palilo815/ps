def yaksu(n):
    ret = 0
    i = 1
    while i * i <= n:
        if n % i == 0:
            ret += 1
        i += 1
    return ret


n = int(input())
ans = 0
for i in range(1, n + 1):
    ans += yaksu(i)
print(ans)
