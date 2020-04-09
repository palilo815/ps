import sys
input = sys.stdin.readline

N = int(input())
arr = list(map(int, input().split()))
v = 0
for i in range(N - 1, -1, -1):
    if arr[i] >= v:
        v = arr[i]
    else:
        v = arr[i] * ((v - 1) // arr[i] + 1)
print(v)
