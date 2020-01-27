T = int(input())
for _ in range(T):
    num = input()
    if int(num[-1]) % 2:
        print("odd")
    else:
        print("even")
