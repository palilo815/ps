import sys
input = sys.stdin.readline

N = int(input())
mine = [0]
for i in range(N):
    mine.append(int(input()))
mine.append(0)

for i in range(1, N + 1):
    if mine[i - 1] <= mine[i] >= mine[i + 1]:
        print(i)
