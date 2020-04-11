import sys
input = sys.stdin.readline

N, M = map(int, input().split())
S = set()
for i in range(N):
    S.add(input())

ans = 0
for i in range(M):
    k = input()
    if k in S:
        ans += 1
print(ans)
