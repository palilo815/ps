T = int(input())
for t in range(1, T + 1):
    print("Scenario #" + str(t) + ":")
    N = int(input())
    word = []
    for _ in range(N):
        word.append(input())
    N = int(input())
    for _ in range(N):
        pw = input().split()
        for i in range(1, int(pw[0]) + 1):
            print(word[int(pw[i])], end="")
        print()
    print()
