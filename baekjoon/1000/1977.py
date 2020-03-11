A = int(input())
B = int(input())
ans = []
i = 1
while i * i < A:
    i += 1
while i * i <= B:
    ans.append(i * i)
    i += 1
if not ans:
    print(-1)
else:
    print(sum(ans))
    print(ans[0])
