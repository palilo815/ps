def need(h):
    return h * h * 2 - 2 * h + 1


n = int(input())
height = 0
while 1:
    block = need(height + 1)
    if n < block:
        break
    height += 1
    n -= block
print(height)
