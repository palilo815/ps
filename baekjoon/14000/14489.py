a, b = map(int, input().split())
c = int(input())
a += b
c *= 2
if a >= c:
    print(a - c)
else:
    print(a)
