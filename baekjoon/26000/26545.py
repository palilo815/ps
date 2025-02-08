def main() -> None:
    n = int(input())
    ans = sum(int(input()) for _ in range(n))
    print(ans)


if __name__ == "__main__":
    main()
