arr = list(map(int, input().split()))
if sum(arr) >= 100:
    print("OK")
else:
    if arr[0] < arr[1]:
        if arr[0] < arr[2]:
            print("Soongsil")
        else:
            print("Hanyang")
    else:
        if arr[1] < arr[2]:
            print("Korea")
        else:
            print("Hanyang")
