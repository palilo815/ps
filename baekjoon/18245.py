gap = 2
while True:
    s = input()
    if s == "Was it a cat I saw?":
        break
    for i in range(0, len(s), gap):
        print(s[i], end="")
    print()
    gap += 1
