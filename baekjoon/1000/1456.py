MAX = 10000000
sieve = [False] * (MAX + 1)
i = 2
while i * i <= MAX:
    if not sieve[i]:
        for j in range(i * i, MAX + 1, i):
            sieve[j] = True
    i += 1

A, B = map(int, input().split())
ans = 0

for i in range(2, MAX + 1):
    if not sieve[i]:
        x = i * i
        while x < A:
            x *= i
        while x <= B:
            x *= i
            ans += 1
print(ans)
