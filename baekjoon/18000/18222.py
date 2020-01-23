def ceil_pow2(n):
    ret, tmp = 1, 2
    while tmp <= n:
        ret = tmp
        tmp *= 2
    return ret


k = int(input())
k -= 1
flip = 0
while k:
    k -= ceil_pow2(k)
    flip += 1
print(flip % 2)
