def check(s):
    for i in range(1, len(s) // 2 + 1):
        if s[-i:] == s[-i * 2:-i]:
            return False
    return True


def solve():
    global s
    if len(s) == N:
        return True
    for i in range(ord('1'), ord('4')):
        s += chr(i)
        if check(s) and solve():
            return True
        s = s[:-1]
    return False


N = int(input())
s = ""
solve()
print(s)
