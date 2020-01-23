A = list(map(int, input().split()))
B = list(map(int, input().split()))
ans = 0
for i in range(3):
    if A[i] < B[i]:
        ans += B[i] - A[i]
print(ans)
