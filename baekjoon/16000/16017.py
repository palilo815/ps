arr = []
for _ in range(4):
    arr.append(int(input()))
if arr[1] == arr[2] and (arr[0] == 8 or arr[0] == 9) and (arr[3] == 8 or arr[3] == 9):
    print("ignore")
else:
    print("answer")
