stdt = [[0] * 7 for i in range(2)]
N, K = map(int, input().split())
for i in range(N):
    sex, grade = map(int, input().split())
    stdt[sex][grade] += 1
ans = 0
for i in range(2):
    for j in range(7):
        if stdt[i][j] > 0:
            ans += (stdt[i][j] - 1) // K + 1
print(ans)
