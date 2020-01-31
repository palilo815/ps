def happy(h):
    if h <= 1:
        return 0
    l = h // 2
    r = h - l
    return l * r + happy(l) + happy(r)


n = int(input())
print(happy(n))
