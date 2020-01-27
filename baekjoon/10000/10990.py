n = int(input())
m = 1
print(' ' * (n - 1) + '*')
for i in range(n - 2, -1, -1):
    print(' ' * i + '*' + ' ' * m + '*')
    m += 2
