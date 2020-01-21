arr = list(map(int, input().split()))
my_scr = int(input())
arr.sort(reverse=True)
for i in range(50):
    if my_scr == arr[i]:
        if i < 5:
            print("A+")
        elif i < 15:
            print("A0")
        elif i < 30:
            print("B+")
        elif i < 35:
            print("B0")
        elif i < 45:
            print("C+")
        elif i < 48:
            print("C0")
        else:
            print("F")
        break;
