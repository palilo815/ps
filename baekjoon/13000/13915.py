input = __import__('sys').stdin.readline

while 1:
    try:
        N = int(input())
    except:
        break
    s = set()
    for i in range(N):
        x = int(input())
        mask = 0
        while x:
            mask |= 1 << (x % 10 - 1)
            x //= 10
        s.add(mask)
    print(len(s))
