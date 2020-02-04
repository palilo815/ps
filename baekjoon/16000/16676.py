n = input()
if len(n) <= 1:
    print(1)
else:
    all_1 = int('1' * len(n))
    # all_1보다 작다면, 똑같은 수가 len(n)번 반복될 일이 없다.
    if int(n) < all_1:
        print(len(n) - 1)
    else:
        print(len(n))
