total, n = int(input()), int(input())
# 가장 간단한 방법 : 1부터 n-1까지의 합 + 나머지
for i in range(1, n):
    print(i)
    total -= i
print(total)
