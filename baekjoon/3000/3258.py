N, Z, M = map(int, input().split())
Z -= 1
wall = [False] * N
arr = list(map(int, input().split()))
for x in arr:
    wall[x - 1] = True

k = 1
while True:
    s = 0
    visited = [False] * N
    while not wall[s] and not visited[s] and s != Z:
        visited[s] = True
        s = (s + k) % N
    if s == Z:
        break
    k += 1
print(k)
