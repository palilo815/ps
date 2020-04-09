import sys
input = sys.stdin.readline

N = int(input())
if N == 0:
    print(0)
    sys.exit(0)

arr = [0] * N
for i in range(N):
    arr[i] = int(input())
arr.sort()

j = (N * 15 + 50) // 100
ans = 0
for i in range(j, N - j):
    ans += arr[i]
print(int(ans / (N - 2 * j) + 0.5))
