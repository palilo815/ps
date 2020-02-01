arr = [[]] * 4
for i in range(4):
    arr[i] = list(map(int, input().split()))
    arr[i].sort(reverse=True)
MIN = arr[0][-1]
Sum = 0
Sale = 0
for i in range(1, 4):
    for j in range(len(arr[i])):
        if j < MIN:
            Sale += arr[i][j] * 0.9
        else:
            Sale += arr[i][j]
        Sum += arr[i][j]
print(Sum)
print(int(Sale))