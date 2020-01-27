a, b = map(int, input().split())
A, B = [], []
for i in range(1, a + 1):
    if a % i == 0:
        A.append(i)
for i in range(1, b + 1):
    if b % i == 0:
        B.append(i)
for x in A:
    for y in B:
        print(x, y)
