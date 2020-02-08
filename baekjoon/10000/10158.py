def mov(pos, wall):
    pos %= (2 * wall)
    if pos > wall:
        pos = 2 * wall - pos
    return pos


row, col = map(int, input().split())
r, c = map(int, input().split())
t = int(input())
r += t
c += t
print(mov(r, row), mov(c, col))
