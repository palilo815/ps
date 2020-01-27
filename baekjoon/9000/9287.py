s = ["Standing", "Fallen"]
T = int(input())
for t in range(1, T + 1):
    n = int(input())
    fallen = 0
    for _ in range(n):
        block = input()
        if block[1] == '0' and (block[0] == '0' or block[2] == '0'):
            fallen = 1
    print("Case", str(t) + ':', s[fallen])
