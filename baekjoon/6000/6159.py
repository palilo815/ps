import sys
input = sys.stdin.readline

N, S = map(int, input().split())
cow = [0] * N
for i in range(N):
    cow[i] = int(input())
cow.sort()
j = N - 1
ans = 0
for i in range(N):
    if cow[i] > S // 2:
        break
    while cow[i] + cow[j] > S:
        j -= 1
    ans += j - i
print(ans)
