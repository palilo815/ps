def rss():
    global arr
    ret = 0
    for j in range(len(arr)):
        ret += (arr[j][1] - (a * arr[j][0] + b)) ** 2
    return ret


N = int(input())
arr = []
for i in range(N):
    arr.append(list(map(int, input().split())))
A, B = 0, 0
MIN = 2100000000
for a in range(1, 101):
    for b in range(1, 101):
        tmp = rss()
        if MIN > tmp:
            MIN, A, B = tmp, a, b
print(A, B)
