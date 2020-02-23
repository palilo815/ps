cache = [[[0 for i in range(21)] for j in range(21)] for k in range(21)]


def w(a, b, c):
    if a <= 0 or b <= 0 or c <= 0:
        return 1
    if a > 20 or b > 20 or c > 20:
        return w(20, 20, 20)
    if cache[a][b][c]:
        return cache[a][b][c]
    if a < b < c:
        cache[a][b][c] = w(a, b, c - 1) + w(a, b - 1, c - 1) - w(a, b - 1, c)
    else:
        cache[a][b][c] = w(a - 1, b, c) + w(a - 1, b - 1, c) + w(a - 1, b, c - 1) - w(a - 1, b - 1, c - 1)
    return cache[a][b][c]


while True:
    a, b, c = map(int, input().split())
    if a == b == c == -1:
        break
    print("w({:d}, {:d}, {:d}) = {:d}".format(a, b, c, w(a, b, c)))
