T = int(input())
for t in range(1, T + 1):
    a = list(map(int, input().split()))
    a.sort()
    # Scenario #1:
    print("Scenario #" + str(t) + ':')
    if a[0] * a[0] + a[1] * a[1] == a[2] * a[2]:
        print("yes")
    else:
        print("no")
    print()
