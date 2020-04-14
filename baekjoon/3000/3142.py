input = __import__('sys').stdin.readline

factor = [0] * 1000001
for i in range(2, 1000001):
    if factor[i]:
        continue
    factor[i] = i
    for j in range(i * i, 1000001, i):
        factor[j] = i

multiplied = [False] * 1000001
N = int(input())
prime_cnt = 0
for _ in range(N):
    num = int(input())
    while num > 1:
        f = factor[num]
        if multiplied[f]:
            prime_cnt -= 1
        else:
            prime_cnt += 1
        multiplied[f] = not multiplied[f]
        num //= f
    print("NE" if prime_cnt else "DA")
