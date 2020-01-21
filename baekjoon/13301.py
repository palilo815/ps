fib = [0] * 80
fib[0] = 1
fib[1] = 1
n = int(input())
for i in range(2, n):
    fib[i] = fib[i - 2] + fib[i - 1]
# 1은 예외다.
if n == 1:
    print(4)
else:
    print(2 * (fib[n - 1] * 2 + fib[n - 2]))
