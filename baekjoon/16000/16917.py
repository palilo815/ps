A, B, C, X, Y = map(int, input().split())
ans = 0
if A + B > 2 * C:
    z = min(X, Y)
    ans += 2 * z * C
    X -= z
    Y -= z
    if X > 0:
        ans += X * min(A, 2 * C)
    if Y > 0:
        ans += Y * min(B, 2 * C)
else:
    ans += A * X + B * Y
print(ans)
