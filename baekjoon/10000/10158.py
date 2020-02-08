def mov(pos, wall):
    while pos < 0 or pos > wall:
        if pos < 0:
            pos = -pos
        else:
            pos = 2 * wall - pos
    return pos


row, col = map(int, input().split())
r, c = map(int, input().split())
t = int(input())
r += t
c += t
print(mov(r, row), mov(c, col))
