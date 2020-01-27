T = int(input())
for _ in range(T):
    score = list(map(int, input().split()))
    score.sort()
    if score[3] - score[1] >= 4:
        print("KIN")
    else:
        print(sum(score[1:4]))
