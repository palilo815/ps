cnt = [6, 2, 5, 5, 4, 5, 6, 3, 7, 6]
L, S = [-1] * 108, [0] * 108

L[0] = 0
S[2], S[3], S[4], S[5], S[6], S[7] = 1, 7, 4, 2, 6, 8

for n in range(99):
    if L[n] != -1:
        for i, c in enumerate(cnt):
            L[n + c] = max(L[n + c], L[n] * 10 + i)
    if S[n]:
        for i, c in enumerate(cnt):
            if S[n + c]:
                S[n + c] = min(S[n + c], S[n] * 10 + i)
            else:
                S[n + c] = S[n] * 10 + i

for t in range(int(input())):
    N = int(input())
    print(S[N], L[N])