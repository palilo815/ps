L, R = map(int, input().split())
tin = max(L, R)
if tin == 0:
    print("Not a moose")
elif L == R:
    print("Even", tin * 2)
else:
    print("Odd", tin * 2)
