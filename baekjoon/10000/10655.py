import sys
input = sys.stdin.readline

def dist(a, b):
    return abs(point[a][0] - point[b][0]) + abs(point[a][1] - point[b][1])


N = int(input())
point = []
for i in range(N):
    point.append(list(map(int, input().split())))

total = 0
for i in range(1, N):
    total += dist(i - 1, i)

jump = 0
for i in range(1, N - 1):
    jump = max(jump, dist(i - 1, i) + dist(i, i + 1) - dist(i - 1, i + 1))
print(total - jump)
