N = int(input())
t = [1]
for i in range(1, N + 1):
    x = 0
    for j in range(i):
        x += t[j] * t[i - j - 1]
    t.append(x)
print(t[N])
