s = input().split('0')
l, r = 0, 0
for x in s[0]:
    if x == '@':
        l += 1
for x in s[1]:
    if x == '@':
        r += 1
print(l, r)
