while 1:
    y = int(input())
    if y == 0:
        break
    print(y, end=' ')
    gap = y - 1896
    if gap < 0 or gap % 4:
        print("No summer games")
    else:
        if 1914 <= y <= 1918 or 1939 <= y <= 1945:
            print("Games cancelled")
        elif y > 2020:
            print("No city yet chosen")
        else:
            print("Summer Olympics")
