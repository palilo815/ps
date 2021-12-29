if __name__ == '__main__':
    x, y = map(int, input().split())
    r = int(input())
    for dx in [-r, r]:
        for dy in [-dx, dx]:
            print(x + dx, y + dy)
