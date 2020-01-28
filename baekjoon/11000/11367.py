T = int(input())
for _ in range(T):
    s, n = input().split()
    n = int(n)
    if n >= 90:
        c = 'A'
    elif n >= 80:
        c = 'B'
    elif n >= 70:
        c = 'C'
    elif n >= 60:
        c = 'D'
    else:
        c = 'F'
    if n == 100 or (n % 10 >= 7 and c != 'F'):
        c += '+'
    print(s, c)
