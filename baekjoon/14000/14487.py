import sys
input = sys.stdin.readline

input()
cost = list(map(int, input().split()))
print(sum(cost) - max(cost))
