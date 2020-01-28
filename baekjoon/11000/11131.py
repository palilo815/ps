T = int(input())
for _ in range(T):
    input()
    val = sum(list(map(int, input().split())))
    if val > 0:
        print("Right")
    elif val < 0:
        print("Left")
    else:
        print("Equilibrium")
