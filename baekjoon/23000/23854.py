def main() -> None:
    a = int(input())
    b = int(input())
    if a % 3 != b % 3:
        print(-1)
        return
    print(a // 3, a % 3, b // 3)


if __name__ == "__main__":
    main()
