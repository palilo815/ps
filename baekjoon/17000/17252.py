N = int(input())
three = N and 1 or 0
while N:
    if N % 3 > 1:
        three = 0
        break
    N //= 3

ans = ["NO", "YES"]
print(ans[three])
