k, a, b = map(int, input().split())
start = 0
 # a < 0인 경우, 수직선을 오른쪽으로 땡긴다.
if a < 0:
    b += -a
    start = -a
    a = 0
tmp = (a - start) // k
start += tmp * k
if start < a:
    start += k
tmp = (b - start) // k
end = start + tmp * k
if end > b:
    end -= k
print((end - start) // k + 1)
