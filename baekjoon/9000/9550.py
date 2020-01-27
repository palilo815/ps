T = int(input())
for _ in range(T):
    N, K = map(int, input().split())
    candy = map(int, input().split())
    ans = 0
    for c in candy:
        ans += c // K
    print(ans)
