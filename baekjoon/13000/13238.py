import sys
input = sys.stdin.readline

N = int(input())
price = list(map(int, input().split()))
ans, buy = 0, 100000
for x in price:
    if buy >= x:
        buy = x
    else:
        ans = max(ans, x - buy)
print(ans)
