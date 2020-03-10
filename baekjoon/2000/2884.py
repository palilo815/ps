H, M = map(int, input().split())
M -= 45
if M < 0:
    H -= 1
    M += 60
if H < 0:
    H += 24
print(H, M)
