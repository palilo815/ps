if __name__ == '__main__':
    input()
    s = input()
    res = 0
    for c in "ABCDE":
        if c in s:
            res += 1
    print("Yes" if res > 2 else "No")
