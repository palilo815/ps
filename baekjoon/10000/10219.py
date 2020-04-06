for t in range(int(input())):
    H, W = map(int, input().split())
    for h in range(H):
        s = input()
        print(s[::-1])
