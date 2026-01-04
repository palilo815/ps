n = int(input())
if n < 100_000:
    m = n // 20
elif n < 500_000:
    m = n // 10
elif n < 1_000_000:
    m = n // 20 * 3
else:
    m = n // 5
print(m, n - m)
