N = int(input())
three = 1
while N:
    if N % 3 > 1:
        three = 0
        break
    N //= 3

ans = ["NO", "YES"]
print(ans[three])
