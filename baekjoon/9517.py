k = int(input())
n = int(input())
time = 210
for _ in range(n):
    t, a = input().split()
    time -= int(t)
    if time < 0:
        break
    if a == 'T':
        k += 1
        if k == 9:
            k = 1
print(k)
