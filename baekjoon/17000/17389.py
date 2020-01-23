N = int(input())
ans = input()
score = 0
bonus = 0
for i in range(N):
    if ans[i] == 'O':
        score += i + 1 + bonus
        bonus += 1
    else:
        bonus = 0
print(score)
