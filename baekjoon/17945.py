import math

b, c = map(int, input().split())
root = int(math.sqrt(b * b - c))
if root == 0:
    print(-b)
else:
    print(-b - root, -b + root)
