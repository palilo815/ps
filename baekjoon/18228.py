N = int(input())
ice = list(map(int, input().split()))
peng = ice.index(-1)
ans = [1000000000, 1000000000]
for i in range(peng):
    ans[0] = min(ans[0], ice[i])
for i in range(peng + 1, len(ice)):
    ans[1] = min(ans[1], ice[i])
print(ans[0] + ans[1])
