a, b, c = map(int, input().split())
ans, coin = 1, 0
while coin < c:
    coin += a
    if ans % 7 == 0:
        coin += b
    ans += 1
print(ans - 1)
