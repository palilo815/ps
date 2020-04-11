row, col = map(int, input().split())
mat = []
for i in range(row):
    mat.append(input())

words = []
for r in range(row):
    words += (mat[r].split('#'))
for c in range(col):
    s = ""
    for r in range(row):
        s += mat[r][c]
    words += (s.split('#'))

ans = "~"
for word in words:
    if len(word) > 1 and word < ans:
        ans = word
print(ans)
