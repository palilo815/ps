from itertools import combinations

N = int(input())
arr = list(map(int, input().split()))
res = set()
for i in range(1, N + 1):
    for c in combinations(arr, i):
        res.add(sum(c))
res = sorted(res)

i = 1
for x in res:
    if x != i:
        break
    i += 1
print(i)