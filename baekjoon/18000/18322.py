N, K = map(int, input().split())
s = input().split()
p_len = 0
for x in s:
    if p_len + len(x) > K:
        print()
        p_len = 0
    print(x, end=' ')
    p_len += len(x)
