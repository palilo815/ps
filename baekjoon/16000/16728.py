def score(x, y):
    dist = x * x + y * y
    global arr
    for i in range(len(arr)):
        if dist <= arr[i]:
            return 10 - i
    return 0


arr = []
for i in range(1, 20, 2):
    arr.append((i * i * 100))
N = int(input())
ans = 0
for _ in range(N):
    x, y = map(int, input().split())
    ans += score(x, y)
print(ans)
