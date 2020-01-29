M = [1, 2, 3, 4]
s = input()
v, h = 0, 0
for x in s:
    if x == 'H':
        h += 1
    else:
        v += 1
h %= 2
v %= 2
if h:
    M[0], M[2] = M[2], M[0]
    M[1], M[3] = M[3], M[1]
if v:
    M[0], M[1] = M[1], M[0]
    M[2], M[3] = M[3], M[2]
print(M[0], M[1])
print(M[2], M[3])
