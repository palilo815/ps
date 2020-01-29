cup = [1, 0, 0]
s = input()
for x in s:
    if x == 'A':
        cup[0], cup[1] = cup[1], cup[0]
    elif x == 'B':
        cup[1], cup[2] = cup[2], cup[1]
    else:
        cup[2], cup[0] = cup[0], cup[2]
print(cup.index(1) + 1)
