input = __import__('sys').stdin.readline

T = int(input())
while T:
    T -= 1
    R, B, M = map(int, input().replace('.', '').split())

    ans = 0
    while 0 < B < 5000001 and ans <= 1200:
        ans += 1
        B = int(B * (1 + R / 10000) + 0.5 + 1e-8)
        B -= M
    print(ans if ans <= 1200 and B < 50001 else "impossible")
