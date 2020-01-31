circle = ["PROBRAIN", "GROW", "ARGOS", "ADMIN", "ANT", "MOTION", "SPG", "COMON", "ALMIGHTY"]
max_scr = -1
input()
for i in range(9):
    scr = max(list(map(int, input().split())))
    if max_scr < scr:
        max_scr = scr
        idx = i
print(circle[idx])
