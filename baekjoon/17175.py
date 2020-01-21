fib = [0] * 51
fib[0] = 1
fib[1] = 1
n = int(input())
for i in range(2, n + 1):
    fib[i] = (fib[i - 1] + fib[i - 2] + 1) % 1000000007
print(fib[n])
