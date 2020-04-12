import sys
input = sys.stdin.readline

N = int(input())
com = []
total = 0
for i in range(N):
    com.append(list(map(int, input().split())))
    total += sum(com[i])

l, r = 0, 10000000
while l <= r:
    m = (l + r) // 2
    cnt = 0
    for row in com:
        for x in row:
            cnt += min(x, m)
    if cnt >= (total + 1) // 2:
        ans = m
        r = m - 1
    else:
        l = m + 1
print(ans)
