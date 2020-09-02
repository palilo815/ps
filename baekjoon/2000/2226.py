N = int(input())
z, o = 0, 1

for i in range(N - 1):
    s = z + o
    z, o = s - (i % 2), s
print(z)