import sys
input = sys.stdin.readline

input()
card = list(map(int, input().split()))
print(sum(card) - max(card))
