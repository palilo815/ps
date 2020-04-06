d = [0, 1, 3, 5]
for _ in range(int(input())):
    N = int(input())
    arr = list(map(int, input().split()))
    ans = 1
    while sum(arr) <= N:
        ans += 1
        tmp = [0] * 6
        for i in range(6):
            for j in range(4):
                tmp[i] += arr[(i + d[j]) % 6]
        arr = tmp
    print(ans)
