if __name__ == '__main__':
    n = int(input())
    print('@' * (n + 2))
    print(('@' + ' ' * n + '@' + '\n') * n, end='')
    print('@' * (n + 2))
