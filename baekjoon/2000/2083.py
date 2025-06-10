while True:
    a, b, c = input().split()
    if a == "#":
        break
    print(a, ["Junior", "Senior"][int(b) > 17 or int(c) >= 80])
