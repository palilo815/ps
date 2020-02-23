N = int(input())
fib = [1] * 3
while len(fib) < N:
    fib.append(fib[-1] + fib[-3])
print(fib[-1])
