N = int(input())
candy = []
for i in range(N):
    candy.append(int(input()))
x = sum(candy) // 2
for i in range(1, N - 1, 2):
    x -= candy[i]
print(x)
for i in range(N - 1):
    print(candy[i] - x)
    x = candy[i] - x
