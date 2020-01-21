T = int(input())
total = [0] * 3
for t in range(T):
    tmp = list(map(int, input().split()))
    total = [total[i] + tmp[i] for i in range(3)]
    pack = min(total)
    if pack < 30:
        print("NO")
    else:
        print(pack)
        for i in range(3):
            total[i] -= pack
