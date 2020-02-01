import sys

T = int(input())
for _ in range(T):
    print(sum(map(int, sys.stdin.readline().split())))
