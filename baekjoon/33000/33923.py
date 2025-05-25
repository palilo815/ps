def main() -> None:
    n, m = map(int, input().split())
    if n == m:
        print((n - 2) ** 2 + 1)
    else:
        n = min(n, m)
        print((n - 1) ** 2)


if __name__ == "__main__":
    main()
