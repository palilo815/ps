# 1-2학년
# 3-4학년 남
# 3-4학년 여
# 5-6학년 남
# 5-6학년 여
cnt = [0] * 5
N, K = map(int, input().split())
for n in range(N):
    sex, age = map(int, input().split())
    if age <= 2:
        cnt[0] += 1
    elif age <= 4:
        if sex:
            cnt[1] += 1
        else:
            cnt[2] += 1
    else:
        if sex:
            cnt[3] += 1
        else:
            cnt[4] += 1
ans = 0
for num in cnt:
    ans += (num - 1) // K + 1
print(ans)
