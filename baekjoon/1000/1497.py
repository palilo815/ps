import sys
from itertools import combinations
input = sys.stdin.readline

N, M = map(int, input().split())
guitar = []
for i in range(N):
    guitar.append(input().split()[1])

max_song, min_guitar = 0, -1
for i in range(1, N + 1):
    for c in combinations(guitar, i):
        check = [0] * M
        for mask in c:
            for j, x in enumerate(mask):
                if x == 'Y':
                    check[j] = 1
        if sum(check) > max_song:
            max_song = sum(check)
            min_guitar = i
print(min_guitar)
