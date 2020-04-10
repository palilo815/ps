def solve(s):
    i = 0
    while i < len(s):
        n = 0
        while i + n < len(s) and s[i + n] == 'w':
            n += 1

        if n == 0 or i + 4 * n > len(s):
            return 0

        o, l, f = i + n, i + 2 * n, i + 3 * n
        while o < i + 2 * n:
            if s[o] != 'o' or s[l] != 'l' or s[f] != 'f':
                return 0
            o += 1
            l += 1
            f += 1
        i += 4 * n
    return 1


s = input()
print(solve(s))