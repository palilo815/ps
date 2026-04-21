def main():
    while (n := int(input())) != 0:
        if n > 5_000_000:
            n = n * 8 // 10
        elif n > 1_000_000:
            n = n * 9 // 10
        print(n)


if __name__ == "__main__":
    main()
