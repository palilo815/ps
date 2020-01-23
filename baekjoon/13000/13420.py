T = int(input())
for t in range(T):
    s = input().split(" ")
    b = int(s[-1])
    a1, a2 = int(s[0]), int(s[2])
    if s[1] == '+':
        a = a1 + a2
    elif s[1] == '-':
        a = a1 - a2
    elif s[1] == '*':
        a = a1 * a2
    else:
        a = a1 // a2
    if a == b:
        print("correct")
    else:
        print("wrong answer")
