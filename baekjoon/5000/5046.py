N, B, H, W = map(int, input().split())
ans = 10001
for i in range(H):
    pay = int(input())
    people = list(map(int, input().split()))
    if max(people) >= N and pay < ans:
        ans = pay
if ans == 10001 or ans * N > B:
    print("stay home")
else:
    print(ans * N)
