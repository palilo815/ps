a = list(map(int, input().split(':')))
b = list(map(int, input().split(':')))
for i in range(2, 0, -1):
    b[i] -= a[i]
    if b[i] < 0:
        b[i] += 60
        b[i - 1] -= 1
b[0] = (b[0] - a[0] + 24) % 24
if b[0] == b[1] == b[2] == 0:
    b[0] = 24
for i in range(3):
    print("{:02d}".format(b[i]), end='')
    if i != 2:
        print(':', end='')
