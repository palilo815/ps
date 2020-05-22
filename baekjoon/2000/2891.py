N, S, R = map(int, input().split())
arr = [1] * N
tmp = list(map(int, input().split()))
for x in tmp: arr[x - 1] -= 1
tmp = list(map(int, input().split()))
for x in tmp: arr[x - 1] += 1

for i in range(N):
    if not arr[i]:
        if i > 0 and arr[i - 1] > 1:
            arr[i] += 1
        if not arr[i] and i < N - 1 and arr[i + 1] > 1:
            arr[i + 1] -= 1
            arr[i] += 1
ans = 0
for x in arr:
    if not x: ans += 1
print(ans)
