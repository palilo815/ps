two = int(input())
e = 0
s = input()
for x in s:
    if x == 'e':
        e += 1
two -= e
if two > e:
    print(2)
elif two < e:
    print('e')
else:
    print("yee")
