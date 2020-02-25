ans = 0
D = []
for _ in range(11):
    d, v = map(int, input().split())
    ans += v * 20
    D.append(d)
D.sort()
T = 0
for d in D:
    T += d
    ans += T
print(ans)
