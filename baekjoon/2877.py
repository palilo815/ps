# 4,7을 이진수 bit처럼 생각
# K번째 수의 bit수를 구한 뒤
# 전부 4로 깐 뒤, 필요한 부분을 7로 만든다.
K = int(input())
bit = 1
while K > 2 ** bit:
    K -= 2 ** bit
    bit += 1
K -= 1
stack = [4] * bit
idx = bit - 1
while K > 0:
    if K % 2 == 1:
        stack[idx] = 7
    K //= 2
    idx -= 1
for x in stack:
    print(x, end="")