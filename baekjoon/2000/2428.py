import sys
input = sys.stdin.readline

N = int(input())
arr = list(map(int, input().split()))
arr.sort()

j, ans = 0, 0
for i in range(N):
    while arr[i] * 9 > arr[j] * 10:
        j += 1
    ans += i - j
print(ans)
