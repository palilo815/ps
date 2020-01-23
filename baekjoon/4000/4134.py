def is_prime(num):
    if num < 2:
        return False
    i = 2
    while i * i <= num:
        if num % i == 0:
            return False
        i += 1
    return True

#노가다로 찾자 그냥..
T = int(input())
for t in range(T):
    N = int(input())
    while not is_prime(N):
        N = N + 1
    print(N)
