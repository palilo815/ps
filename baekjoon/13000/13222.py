N, w, h = map(int, input().split())
dia = w * w + h * h
for _ in range(N):
    x = int(input())
    if x * x <= dia:
        print("YES")
    else:
        print("NO")
