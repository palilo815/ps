import sys
input = sys.stdin.readline

N, M = map(int, input().split())
score = list(map(int, input().split()))
idx, scr = 0, -1
for i in range(M):
    arr = input().split()
    t_i = int(arr[0])
    t_s = 0
    for j in range(1, N + 1):
        if arr[j] == 'O':
            t_s += score[j - 1]
    if t_s > scr:
        scr = t_s
        idx = t_i
    elif t_s == scr and idx > t_i:
        idx = t_i
print(idx, scr)
