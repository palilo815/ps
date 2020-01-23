# 한 자리 약수의 개수를 세서 출력한다.
# 만약 약수에 한 자리 이상의 수가 있다면 -1
T = int(input())
for t in range(T):
    n = int(input())
    ans = 0
    for i in range(9, 1, -1):
        while n % i == 0:
            n //= i
            ans += 1
    # special case : n == 1일 경우
    ans = max(1, ans)
    if n != 1:
        ans = -1
    print(ans)
