T = int(input())
for t in range(1, T + 1):
    print("Scenario #" + str(t) + ":")
    a, b = map(int, input().split())
    print((a + b) * (b - a + 1) // 2)
    print()
