if __name__ == '__main__':
    n = int(input())
    print(('@' *  n + ' ' * 3 * n + '@' *  n + '\n') * 2 * n, end='')
    print(('@' * 5 * n + '\n') * n, end='')
    print(('@' *  n + ' ' * 3 * n + '@' *  n + '\n') * n, end='')
    print(('@' * 5 * n + '\n') * n, end='')

