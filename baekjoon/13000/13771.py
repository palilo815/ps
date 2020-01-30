N = int(input())
a = []
for _ in range(N):
    a.append(float(input()))
a.sort()
print("%.2f" % a[1])
