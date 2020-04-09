T = int(input())
M = int(input())
edge = []
while M:
    M -= 1
    u, v, w = input().split()
    edge.append([ord(u) - ord('A'), ord(v) - ord('A'), float(w)])
ans = [0.25, 0.25, 0.25, 0.25]
while T:
    T -= 1
    tmp = [0, 0, 0, 0]
    for u, v, w in edge:
        tmp[v] += ans[u] * w
    ans = tmp
for x in ans:
    print("%.3f" % (x * 100))
