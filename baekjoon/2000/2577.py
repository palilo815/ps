n = 1
for _ in range(3):
    n *= int(input())
cnt = [0] * 10
while n:
    cnt[n % 10] += 1
    n //= 10
for x in cnt:
    print(x)
