arr = [0 for _ in range(201)]
N = int(input())
MAX = 0 # 입력 범위 체크용
for _ in range(N):
    x = int(input())
    MAX = max(MAX, x)
    arr[x] = 1
# 사용된 숫자는 arr[] = 1로 되어있다.
for i in range(1, MAX):
    if arr[i] == 0:
        print(i)
        arr[0] = 1
# arr[0] : flag 역할
if arr[0] == 0:
    print("good job")
