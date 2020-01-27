def retest(ans):
    for i in range(10):
        if ans[i] != (i % 5) + 1:
            return False
    return True


N = int(input())
for i in range(N):
    arr = list(map(int, input().split()))
    if retest(arr):
        print(i + 1)
