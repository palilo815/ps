import sys
input = sys.stdin.readline

while 1:
    N = int(input())
    if N == 0:
        break
    txt = []
    for i in range(N):
        txt.append(input())
    ans = 0
    for i in range(N):
        while ans < len(txt[i]) - 1 and txt[i][ans] != ' ':
            ans += 1
    print(ans + 1)
