def digital_root(n):
    ret = 0
    while n > 0:
        ret += n % 10
        n //= 10
    if ret < 10:
        return ret
    return digital_root(ret)


while True:
    N = int(input())
    if N == 0:
        break
    print(digital_root(N))
