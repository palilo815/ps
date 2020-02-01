n, k = map(int, input().split())
name = []
for _ in range(n):
    name.append(input())
name.sort()
print(name[k - 1])
