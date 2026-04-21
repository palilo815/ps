import sys


def main():
    data = sys.stdin.read()
    ans = (
        (data.count("A") * 4)
        + (data.count("K") * 3)
        + (data.count("Q") * 2)
        + data.count("J")
    )
    print(ans)


if __name__ == "__main__":
    main()
