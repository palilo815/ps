import sys

for N in sys.stdin:
    N = int(N)
    ans = 1
    mod = 1 % N
    while mod:
        ans += 1
        mod = (mod * 10 + 1) % N
    print(ans)
