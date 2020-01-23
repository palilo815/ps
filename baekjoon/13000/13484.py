X = int(input())
N = int(input())
X *= N + 1
for i in range(N):
    spent = int(input())
    X -= spent
print(X)
