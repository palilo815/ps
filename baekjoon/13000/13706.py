N = int(input())
s, e = 0, 10 ** 800
while 1:
    m = s + (e - s) // 2
    M = m * m
    if M == N:
        break
    elif M > N:
        e = m - 1
    else:
        s = m + 1
print(m)
