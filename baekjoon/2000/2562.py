max_N = int(input())
idx = 1
for i in range(2, 10):
    N = int(input())
    if N > max_N:
        max_N = N
        idx = i
print(max_N)
print(idx)
