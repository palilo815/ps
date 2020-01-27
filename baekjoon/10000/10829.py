N = int(input())
stk = []
while N:
    stk.append(N % 2)
    N //= 2
for i in range(len(stk) - 1, -1, -1):
    print(stk[i], end="")
