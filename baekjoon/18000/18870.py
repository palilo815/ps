import bisect
input = __import__('sys').stdin.readline

N = int(input())
arr = list(map(int, input().split()))
key = list(sorted(set(arr)))

for x in arr:
    print(bisect.bisect_left(key, x), end=' ')
