n = int(input())
a = [int(input()) for _ in range(n)]
m = int(input())
print(sum(a[int(input()) - 1] for _ in range(m)))
