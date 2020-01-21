N = input()
S = 0
zero = False
for c in N:
    num = int(c)
    if num == 0:
        zero = True
    S += num
if S % 3 == 0 and zero:
    N = sorted(N, reverse=True)
    for c in N:
        print(c, end="")
else:
    print(-1)
