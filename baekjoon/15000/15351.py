for _ in range(int(input())):
    s = input()
    score = 0
    for x in s:
        if x != ' ':
            score += ord(x) - ord('A') + 1
    if score == 100:
        score = "PERFECT LIFE"
    print(score)
