T = int(input())
for _ in range(T):
    total, score = 0, 1
    s = input()
    for c in s:
        if c == 'O':
            total += score
            score += 1
        else:
            score = 1
    print(total)
