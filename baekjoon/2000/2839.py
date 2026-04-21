def main():
    n = int(input())
    three = 0
    while n >= 0:
        if n % 5 == 0:
            print(three + n // 5)
            break
        n -= 3
        three += 1
    else:
        print(-1)


if __name__ == "__main__":
    main()
