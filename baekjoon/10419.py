T = int(input())
for t in range(T):
    n = int(input())
    i = 0
    while i * (i + 1) <= n:
        i += 1
    print(i - 1)
