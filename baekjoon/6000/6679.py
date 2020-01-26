def sum_digits(n, d):
    ret = 0
    while n > 0:
        ret += n % d
        n //= d
    return ret


for i in range(1000, 10000):
    if sum_digits(i, 10) == sum_digits(i, 12) == sum_digits(i, 16):
        print(i)
