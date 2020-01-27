n = int(input())
m = 1
print(' ' * (n - 1) + '*')
for i in range(n - 2, 0, -1):
    print(' ' * i + '*' + ' ' * m + '*')
    m += 2
if n != 1:
    print('*' * (2 * n - 1))
