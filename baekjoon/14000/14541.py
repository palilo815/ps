while 1:
    N = int(input())
    if N == -1:
        break
    prev, ans = 0, 0
    for i in range(N):
        speed, dist = map(int, input().split())
        ans += speed * (dist - prev)
        prev = dist
    print(ans, "miles")
