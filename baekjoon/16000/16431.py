Br, Bc = map(int, input().split())
Dr, Dc = map(int, input().split())
Jr, Jc = map(int, input().split())

bessie = max(abs(Jr - Br), abs(Jc - Bc))
daisy = abs(Dr - Jr) + abs(Dc - Jc)

if bessie < daisy:
    print("bessie")
elif bessie > daisy:
    print("daisy")
else:
    print("tie")
