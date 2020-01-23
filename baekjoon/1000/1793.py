from sys import stdin

DP = [0] * 251
DP[0] = 1
DP[1] = 1
for i in range(2, 251):
    # [i-1]에서 | 추가 + [i-2]에서 = 또는 ㅁ추가
    DP[i] = DP[i - 1] + 2 * DP[i - 2]
for N in stdin:
    if N == '':
        break
    print(DP[int(N)])
