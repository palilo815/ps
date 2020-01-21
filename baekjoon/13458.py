N = int(input())
arr = list(map(int, input().split()))
B, C = map(int, input().split())

# 총감독관을 하나씩 둔다.
ans = N
for n in arr:
    # 총감독관이 B명 감시
    n -= B
    # 만약 학생이 남을시 부감독관이 C명 감시
    if n > 0:
        ans += (n - 1) // C + 1
print(ans)
