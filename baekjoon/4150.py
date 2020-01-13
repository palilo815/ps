def multiply(m):
    x = f[0][0] * m[0][0] + f[0][1] * m[1][0]
    y = f[0][0] * m[0][1] + f[0][1] * m[1][1]
    z = f[1][0] * m[0][0] + f[1][1] * m[1][0]
    w = f[1][0] * m[0][1] + f[1][1] * m[1][1]
    f[0][0] = x
    f[0][1] = y
    f[1][0] = z
    f[1][1] = w


def power(n):
    if n == 0 or n == 1:
        return
    m = [[1, 1], [1, 0]]
    power(n // 2)
    multiply(f)
    if n % 2 == 1:
        multiply(m)


def fib(n):
    if n == 0:
        return 0
    power(n - 1)
    return f[0][0]


global f
f = [[1, 1], [1, 0]]
N = int(input())
print(fib(N))
