import sys
input = sys.stdin.readline

N, Q = map(int, input().split())
arr = list(map(int, input().split()))
arr.sort()

psum = [0]
for x in arr:
    psum.append(psum[-1] + x)

while Q:
    Q -= 1
    l, r = map(int, input().split())
    print(psum[r] - psum[l - 1])
