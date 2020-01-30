N, k = map(int, input().split())
drink = []
for _ in range(N):
    drink.append(int(input()))
ans, l, r = 0, 1, 2 ** 31 - 1
while l <= r:
    count = 0
    mid = l + (r - l) // 2
    for i in range(N):
        count += drink[i] // mid
    if count >= k:
        ans = mid
        l = mid + 1
    else:
        r = mid - 1
print(ans)
