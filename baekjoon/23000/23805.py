if __name__ == '__main__':
    n = int(input())
    a, b = '@' * n, ' ' * n
    print((3 * a + b + a + '\n') * n, end='')
    print(((a + b + a + b + a + '\n') * 3 * n), end='')
    print((a + b + 3 * a + '\n') * n, end='')

