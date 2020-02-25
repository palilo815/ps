import sys
input = sys.stdin.readline

N = int(input())
arr = []
for _ in range(N):
    arr.append(int(input()))
ordered = 1
i = arr.index(N) - 1
while i >= 0:
    if arr[i] == N - ordered:
        ordered += 1
    i -= 1
print(N - ordered)
