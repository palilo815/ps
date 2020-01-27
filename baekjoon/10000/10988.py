def pallin(s):
    l, r = 0, len(s) - 1
    while l < r:
        if s[l] != s[r]:
            return 0
        l += 1
        r -= 1
    return 1


s = input()
print(pallin(s))
