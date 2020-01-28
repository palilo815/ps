dominant = {
    "A": 11,
    "K": 4,
    "Q": 3,
    "J": 20,
    "T": 10,
    "9": 14,
    "8": 0,
    "7": 0
}
non_dominant = {
    "A": 11,
    "K": 4,
    "Q": 3,
    "J": 2,
    "T": 10,
    "9": 0,
    "8": 0,
    "7": 0
}
ans = 0
N, S = input().split()
for i in range(int(N) * 4):
    card = input()
    if card[1] == S:
        ans += dominant[card[0]]
    else:
        ans += non_dominant[card[0]]
print(ans)
