if __name__ == '__main__':
    n = int(input())
    print(('@' * 5 * n + '\n') * n, end='')
    print(('@' * n + '\n') * n, end='')
    print(('@' * 5 * n + '\n') * n, end='')
    print(('@' * n + '\n') * 2 * n, end='')
