n, m, t = map(int, input().split())
if n > m:
    n, m = m, n

N, M = t // n, 0
t %= n
max_b, min_c = N, t

while N:
    N -= 1
    t += n
    if t >= m:
        M += 1
        t -= m
        if t < min_c:
            min_c = t
            max_b = N + M

print(max_b, min_c)
