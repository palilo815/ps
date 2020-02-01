mov = [[1, 0], [0, 1], [-1, 0], [0, -1]]
Len = 1.0
V, X, Y = 0, 0, 0
N = int(input())
while N > 0:
    Y += mov[V][0] * min(int(Len), N)
    X += mov[V][1] * min(int(Len), N)
    N -= int(Len)
    Len += 0.5
    V = (V + 1) % 4
print(X, Y)
