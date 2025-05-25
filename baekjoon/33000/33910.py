input = __import__("sys").stdin.readline


def main() -> None:
    _ = int(input())
    a = list(map(int, input().split()))
    ans = 0
    mn = float("inf")
    for x in reversed(a):
        mn = min(mn, x)
        ans += mn
    print(ans)


if __name__ == "__main__":
    main()
