T = int(input())
for _ in range(T):
    arr = list(map(int, input().split()))
    S = max(arr)
    B = sum(arr) - S
    print(S * S + B * B)
