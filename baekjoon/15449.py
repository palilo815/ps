L = list(map(int, input().split()))
L.sort()
ans = 0
for i in range(3):
    for j in range(i + 1, 4):
        for k in range(j + 1, 5):
            if L[i] + L[j] > L[k]:
                ans += 1
print(ans)
