T = int(input())
for _ in range(T):
    ans = list(input().split())
    while True:
        sound = list(input().split())
        if sound[-1] == "say?":
            break
        ans = [x for x in ans if x != sound[-1]]
    for x in ans:
        print(x, end=" ")
    print()
