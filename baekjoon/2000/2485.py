import sys

input = sys.stdin.readline


def gcd(a, b):
    if a == 0:
        return b
    return gcd(b % a, a)


N = int(input())
tree = []
for i in range(N):
    tree.append(int(input()))
tree.sort()

g = tree[1] - tree[0]
for i in range(2, N):
    g = gcd(g, tree[i] - tree[i - 1])

ans = 0
for i in range(1, N):
    ans += (tree[i] - tree[i - 1]) // g - 1
print(ans)
