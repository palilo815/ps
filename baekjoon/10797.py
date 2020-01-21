N = input()
ans = 0
cars = list(input().split())
for car in cars:
    if car == N:
        ans += 1
print(ans)
