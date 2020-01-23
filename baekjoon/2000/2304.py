arr = [0 for i in range(1001)]
N = int(input())
MAX = 0
for i in range(N):
    pos, h = map(int, input().split())
    arr[pos] = h
    MAX = max(MAX, h)
# MAX 에는 가장 높은 기둥이 들어있다.
L, R, ans = 0, 1000, 0

# 왼쪽 끝에서 MAX 기둥까지 움직이면서 면적을 구해준다.
h = 0
while arr[L] != MAX:
    h = max(h, arr[L])
    ans += h
    L += 1

# 오른쪽도 마찬가지
h = 0
while arr[R] != MAX:
    h = max(h, arr[R])
    ans += h
    R -= 1

# MAX 기둥이 하나가 아닐 수 있으므로 +만 하면 안된다.
ans += MAX * (R - L + 1)
print(ans)
