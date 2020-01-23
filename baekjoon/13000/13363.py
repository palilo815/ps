A = int(input())
B = int(input())
clock = B - A
if clock < 0:
    clock += 360
anti_clock = clock - 360
if abs(clock) <= abs(anti_clock):
    print(clock)
else:
    print(anti_clock)
