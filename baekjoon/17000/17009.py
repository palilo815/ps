A, B = 0, 0
for i in range(3, 0, -1):
    A += int(input()) * i
for i in range(3, 0, -1):
    B += int(input()) * i
if A > B:
    print('A')
elif A < B:
    print('B')
else:
    print('T')
