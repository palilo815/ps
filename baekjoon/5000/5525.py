import sys
input = sys.stdin.readline

N = int(input())
L = int(input())
s = input()
ans, i = 0, 0
while i < L:
    if s[i] == 'I':
        j = i + 1
        cnt = 0
        while j + 1 < L and s[j] == 'O' and s[j + 1] == 'I':
            j += 2
            cnt += 1
        ans += max(0, cnt + 1 - N)
        i = j
    else:
        i += 1
print(ans)
