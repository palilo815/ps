def main() -> None:
    s, c, o, n = map(int, input().split())
    s += n
    c += 2 * o
    print(min(s // 3, c // 6))


if __name__ == "__main__":
    main()
