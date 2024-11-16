def main():
    t = int(input())
    for _ in range(t):
        p, t = map(int, input().split())
        print(p - (t // 7) + (t // 4))


if __name__ == "__main__":
    main()
