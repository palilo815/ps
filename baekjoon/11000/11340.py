T = int(input())
for _ in range(T):
    val = 9000
    a, b, c = map(int, input().split())
    val -= a * 15 + b * 20 + c * 25
    val = (val - 1) // 40 + 1
    if val > 100:
        print("impossible")
    else:
        print(val)
