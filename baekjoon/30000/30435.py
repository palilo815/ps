def main():
    dice = [list(map(int, input().split())) for _ in range(3)]

    def ok(me: list[int], enemy: list[int]):
        c1 = sum(1 for x in me for y in enemy if x > y)
        c2 = sum(1 for x in me for y in enemy if x < y)
        return c1 >= c2 and c1 != 0

    for i in range(3):
        a = dice[i]
        b = dice[(i + 1) % 3]
        c = dice[(i + 2) % 3]
        if ok(a, b) and ok(a, c):
            print(i + 1)
            return
    print("No dice")


if __name__ == "__main__":
    main()
