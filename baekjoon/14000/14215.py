a = list(map(int, input().split()))
a.sort()
a[2] = min(a[2], a[0] + a[1] - 1)
print(sum(a))
