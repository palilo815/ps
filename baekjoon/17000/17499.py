import sys
input = sys.stdin.readline

N, Q = map(int, input().split())
arr = list(map(int, input().split()))
idx = 0
while Q:
    Q -= 1
    query = list(map(int, input().split()))
    if query[0] == 1:
        arr[(idx + query[1] - 1) % N] += query[2]
    elif query[0] == 2:
        idx = (idx + N - query[1]) % N
    else:
        idx = (idx + query[1]) % N

for i in range(N):
    print(arr[(idx + i) % N], end=' ')
