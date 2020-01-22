pado = [0, 1, 1, 1, 2]
for i in range(5, 101):
    pado.append(pado[i - 5] + pado[i - 1])
T = int(input())
for _ in range(T):
    n = int(input())
    print(pado[n])
