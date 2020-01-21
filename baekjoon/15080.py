A = input().split()
B = input().split()
T = []
for i in range(0, 6, 2):
    T.append(int(B[i]) - int(A[i]))
ans = T[2] + 60 * T[1] + 3600 * T[0]
if ans < 0:
    ans += 60 * 60 * 24
print(ans)
