import sys
input = sys.stdin.readline

N, Q = map(int, input().split())
psum = [[0, 0, 0]]
while N:
    N -= 1
    x = int(input())
    psum.append(psum[-1][:])
    psum[-1][x - 1] += 1
while Q:
    Q -= 1
    l, r = map(int, input().split())
    for i in range(3):
        print(psum[r][i] - psum[l - 1][i], end=' ')
    print()
