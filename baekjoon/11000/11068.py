def base_cnv(n, b):
    ret = []
    while n:
        ret.append(n % b)
        n //= b
    return ret


for _ in range(int(input())):
    N = int(input())
    find = 0
    b = 2
    while not find and b <= 64:
        num = base_cnv(N, b)
        if num == num[::-1]:
            find = 1
        b += 1
    print(find)
