def main():
    while True:
        x, y = map(int, input().split())
        if not x and not y:
            break
        if x + y == 13:
            print("Never speak again.")
        elif x > y:
            print("To the convention.")
        elif x < y:
            print("Left beehind.")
        else:
            print("Undecided.")


if __name__ == "__main__":
    main()
