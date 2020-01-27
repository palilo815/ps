T = int(input())
for _ in range(T):
    s = input()
    if s[len(s) // 2] == s[len(s) // 2 - 1]:
        print("Do-it")
    else:
        print("Do-it-Not")
