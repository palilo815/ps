import sys
input = sys.stdin.readline

N = int(input())
arr = [0] * N
for i in range(N):
    arr[i] = int(input())
arr.sort()

for i in range(N):
    if arr[i] <= i:
        print(i + 1)
        sys.exit(0)
print(0)
