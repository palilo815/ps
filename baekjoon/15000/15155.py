day, page = map(int, input().split())
use = list(map(int, input().split()))
ans, curr = 1, 0
for n in use:
    if curr + n > page:
        ans += 1
        curr = 0
    curr += n
print(ans)
