def main() -> None:
    n = int(input())
    dp = [0] * (n + 1)
    dp[0] = 1
    for x in range(1, n + 1, 2):
        for i in range(x, n + 1):
            dp[i] += dp[i - x]
    print(dp[n])


if __name__ == "__main__":
    main()
