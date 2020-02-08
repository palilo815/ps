def mov(pos, wall):
    # 2*wall 만큼 전진하면 제자리다.
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
