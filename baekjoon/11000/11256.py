import sys
input = sys.stdin.readline

for t in range(int(input())):
    candy, N = map(int, input().split())
    box = []
    for i in range(N):
        x, y = map(int, input().split())
        box.append((x * y))
    box.sort(reverse=True)
    for i in range(N):
        candy -= box[i]
        if candy <= 0:
            print(i + 1)
            break
