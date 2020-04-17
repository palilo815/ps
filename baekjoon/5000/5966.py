input = __import__('sys').stdin.readline

for _ in range(int(input())):
    N, arr = input().rstrip().split()
    cnt = 0
    valid = True
    for x in arr:
        if x == '>': cnt += 1
        else:
            if cnt: cnt -= 1
            else:
                valid = False
                break
    if cnt: valid = False
    print("legal" if valid else "illegal")
