len_a, len_b, N = map(int, input().split())
a = list(input().split())
b = list(input().split())
goal = list(input().split())
A, B = 0, 0
for i in range(N):
    if goal[i] in a:
        A += 1
    else:
        B += 1
if A > B:
    print('A')
elif A < B:
    print('B')
else:
    print("TIE")
