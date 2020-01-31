def tidy(num):
    prev = 10
    while num > 0:
        if num % 10 > prev:
            return False
        prev = num % 10
        num //= 10
    return True


T = int(input())
for t in range(1, T + 1):
    N = int(input())
    # 직접 1씩 빼면서 일일히 검사한다.
    while not tidy(N):
        N -= 1
    print("Case #" + str(t) + ":", N)
