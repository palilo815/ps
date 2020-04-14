input = __import__('sys').stdin.readline

# factor[i] = i를 나누어 떨어지게 하는 가장 작은 소수
factor = [0] * 1000001
for i in range(2, 1000001):
    if factor[i]:
        continue
    factor[i] = i
    for j in range(i * i, 1000001, i):
        factor[j] = i

# multiplied[i] = 현재 기계에 i가 곱해져 있는가?
# (소수만 곱하므로 소수가 아닌 인덱스는 사용하지 않는다.)
multiplied = [False] * 1000001

# prime_cnt = (multiplied[i] == True)인 i의 개수
prime_cnt = 0

N = int(input())
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
