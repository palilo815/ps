def sleep(n):
    global arr
    while n:
        arr[n % 10] = 1
        n //= 10
    return sum(arr) == 10


T = int(input())
for t in range(1, T + 1):
    N = int(input())
    if N == 0:
        print("Case #" + str(t) + ": INSOMNIA")
    else:
        arr = [0] * 10
        num = N
        while not sleep(num):
            num += N
        print("Case #" + str(t) + ":", num)
