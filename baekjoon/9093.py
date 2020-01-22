T = int(input())
for _ in range(T):
    s = input().split()
    for sub in s:
        print(sub[::-1], end=' ')
    print()
