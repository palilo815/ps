if __name__ == '__main__':
    a, b, c = map(int, input().split())
    print(3 * max(a, b, c) - a - b - c)
