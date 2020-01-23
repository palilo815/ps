def solve(num):
    for a in range(1, 1000):
        A = a * (a + 1) // 2
        if 3 * A > num:
            break
        for b in range(a, 1000):
            B = b * (b + 1) // 2
            if A + 2 * B > num:
                break
            for c in range(b, 1000):
                C = c * (c + 1) // 2
                if A + B + C == num:
                    return 1
                if A + B + C > num:
                    break
    return 0


N = int(input())
for n in range(N):
    K = int(input())
    print(solve(K))
