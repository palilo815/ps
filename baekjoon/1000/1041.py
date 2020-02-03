N = int(input())
A, B, C, D, E, F = map(int, input().split())
if N == 1:
    print(A + B + C + D + E + F - max(A, B, C, D, E, F))
else:
    sum_2 = [A + B, A + C, A + D, A + E, B + C, B + D, B + F, C + E, C + F, D + E, D + F, E + F]
    sum_3 = [A + B + C, A + B + D, A + C + E, A + D + E, B + C + F, B + D + F, C + E + F, D + E + F]

    min_1 = min(A, B, C, D, E, F)
    min_2 = min(sum_2)
    min_3 = min(sum_3)
    
    # 윗 면의 꼭짓점 4개
    ans = 4 * min_3
    # 8개의 모서리 + 4개의 아랫면 꼭짓점
    ans += min_2 * (8 * (N - 2) + 4)
    # 면 5개 (윗면만 정사각형)
    ans += min_1 * ((N - 2) * (N - 2) + (N - 2) * (N - 1) * 4)
    print(ans)
