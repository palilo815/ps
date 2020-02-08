n = input()
half = len(n) // 2
L = n[:half]
R = n[half:]
l, r = 0, 0
for x in L:
    l += int(x)
for x in R:
    r += int(x)
if l == r:
    print("LUCKY")
else:
    print("READY")
