def main():
    a = [int(input()) for _ in range(4)]
    print("ignore" if a[1] == a[2] and a[0] in (8, 9) and a[3] in (8, 9) else "answer")


if __name__ == "__main__":
    main()
