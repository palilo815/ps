N = int(input())
ans = 1
while N != 1:
    ans += 1
    if N % 2:
        N = 3 * N + 1
    else:
        N //= 2
print(ans)
