if __name__ == '__main__':
    n = int(input())
    print(('@' * n + '\n') * 4 * n, end='')
    print(('@' * 5 * n + '\n') * n, end='')

