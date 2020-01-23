while 1:
    L, N = map(int, input().split())
    if L == 0:
        break
    key = list(map(int, input().split()))
    ans = 0
    for _ in range(N):
        flag = True
        x = list(map(int, input().split()))
        for i in range(L):
            if key[i] < x[i]:
                flag = False
                break
        if flag:
            ans += 1
    print(ans)
