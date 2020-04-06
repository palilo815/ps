import sys
input = sys.stdin.readline

N = int(input())
if N == 2:
    print("1 1")
    sys.exit(0)
mat = []
for i in range(N):
    mat.append(list(map(int, input().split())))
x = sum(mat[0])
if N % 2:
    for i in range(1, N, 2):
        x -= mat[i][i + 1]
    x //= (N - 1)
else:
    for i in range(0, N, 2):
        x -= mat[i][i + 1]
    x //= (N - 2)
print(x, end=' ')
for i in range(1, N):
    print(mat[0][i] - x, end=' ')
