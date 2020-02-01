N = int(input())
input()
i = 2
flag = True
while i * i <= N:
    if N % i == 0:
        flag = False
        break
    i += 1
if flag:
    print("Yes")
else:
    print("No")
