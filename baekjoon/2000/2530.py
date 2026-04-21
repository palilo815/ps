def main():
    h, m, s = map(int, input().split())
    t = h * 3600 + m * 60 + s + int(input())
    h = t // 3600 % 24
    m = t // 60 % 60
    s = t % 60
    print(h, m, s)


if __name__ == "__main__":
    main()
