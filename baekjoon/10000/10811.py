N, M = map(int, input().split())
basket = list(range(1, N + 1))
for _ in range(M):
    a, b = map(int, input().split())
    basket[a - 1:b] = basket[a - 1:b][::-1]
for x in basket:
    print(x, end=" ")
