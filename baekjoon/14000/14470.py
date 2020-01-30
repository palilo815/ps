T = []
for i in range(5):
    T.append(int(input()))
ans = 0
if T[0] < 0:
    ans += abs(T[0]) * T[2] + T[3]
    T[0] = 0
ans += (T[1] - T[0]) * T[4]
print(ans)
