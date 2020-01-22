T = int(input())
for _ in range(T):
    angle = list(map(int, input().split()))
    for a in angle:
        print(a, end=' ')
    if sum(angle) == 180:
        print("Seems OK")
    else:
        print("Check")
