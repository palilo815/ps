n, k = map(int, input().split())
use = list(map(int, input().split()))
tap = []
ans = 0
for i in range(k):
    if use[i] in tap:
        continue

    if len(tap) < n:
        tap.append(use[i])
    else:
        tmp = tap[:]
        j = i + 1
        while j < k and len(tmp) > 1:
            if use[j] in tmp:
                tmp.remove(use[j])
            j += 1
        tap.remove(tmp[0])
        tap.append(use[i])
        ans += 1
print(ans)
