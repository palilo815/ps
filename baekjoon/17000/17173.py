N, M = map(int, input().split())
arr = list(map(int, input().split()))
ans = 0
for n in range(1, N + 1):
    for i in range(M):
        if n % arr[i] == 0:
            ans += n
            break
        elif n < arr[i]:
            break
print(ans)
