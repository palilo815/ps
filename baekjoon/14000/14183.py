def main():
    while True:
        _, n = map(int, input().split())
        if n == 0:
            break
        key = list(map(int, input().split()))
        ans = sum(
            all(k >= b for k, b in zip(key, map(int, input().split())))
            for _ in range(n)
        )
        print(ans)


if __name__ == "__main__":
    main()
