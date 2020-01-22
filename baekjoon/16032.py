while 1:
    N = int(input())
    if N == 0:
        break
    arr = list(map(int, input().split()))
    avg = sum(arr) // N
    ans = 0
    for n in arr:
        if avg >= n:
            ans += 1
    print(ans)
