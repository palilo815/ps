arr = list(map(int, input().split()))
for i in range(len(arr)):
    arr[i] -= 11
Time = arr[0] * 60 * 24 + arr[1] * 60 + arr[2]
if Time < 0:
    Time = -1
print(Time)
