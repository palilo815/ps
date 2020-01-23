def solve(n):
    ret = 0
    d = n // 3
    ret += d * (d + 1) // 2 * 3
    d = n // 7
    ret += d * (d + 1) // 2 * 7
    d = n // 21
    ret -= d * (d + 1) // 2 * 21
    return ret


T = int(input())
arr = map(int, input().split())
for num in arr:
    print(solve(num))
