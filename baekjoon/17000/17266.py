import sys
input = sys.stdin.readline

N = int(input())
M = int(input())
light = list(map(int, input().split()))
ans = max(light[0], N - light[-1])
for i in range(0, M - 1):
    ans = max(ans, (light[i + 1] - light[i] + 1) // 2)
print(ans)
