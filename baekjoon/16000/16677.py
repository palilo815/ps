def solve(word):
    global s
    if len(s) > len(word):
        return -1
    i = 0
    for c in word:
        if c == s[i]:
            i += 1
            if i == len(s):
                return len(word) - len(s)
    return -1


s = input()
N = int(input())
a, b = -1, 1
for i in range(N):
    word, c = input().split()
    c = int(c)
    d = solve(word)
    if d == -1:
        continue
    if a * d < b * c:
        a, b = c, d
        ans = word
if a == -1:
    print("No Jam")
else:
    print(ans)
