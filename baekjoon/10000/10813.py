N, M = map(int, input().split())
basket = list(range(1, N + 1))
for _ in range(M):
    a, b = map(int, input().split())
    a -= 1
    b -= 1
    basket[a], basket[b] = basket[b], basket[a]
for x in basket:
    print(x, end=" ")
