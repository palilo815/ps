import sys
input = sys.stdin.readline

T = int(input())
for t in range(1, T + 1):
    N = int(input())
    arr = list(map(int, input().split()))

    odd, even = [], []
    for x in arr:
        if x % 2:
            odd.append(x)
        else:
            even.append(x)

    odd.sort()
    even.sort(reverse=True)

    i, j = 0, 0
    print("Case #%d: " % t, end='')
    for x in arr:
        if x % 2:
            print(odd[i], end=' ')
            i += 1
        else:
            print(even[j], end=' ')
            j += 1
    print()
