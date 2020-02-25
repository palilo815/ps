import sys
input = sys.stdin.readline

input()
arr = list(map(int, input().split()))
gis = []
last = 0
for x in arr:
    if x > last:
        gis.append(x)
        last = x
print(len(gis))
print(*gis, sep=' ')
