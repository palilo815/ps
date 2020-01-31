x = int(input())
y = int(input())
if x > 0:
    if y > 0:
        c = 1
    else:
        c = 4
else:
    if y > 0:
        c = 2
    else:
        c = 3
print(c)
