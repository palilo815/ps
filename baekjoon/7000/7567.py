s = input()
h = 10
for i in range(1, len(s)):
    if s[i] == s[i - 1]:
        h += 5
    else:
        h += 10
print(h)
