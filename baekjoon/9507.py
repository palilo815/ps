K = [1, 1, 2, 4]
for i in range(4, 68):
    K.append(K[i - 4] + K[i - 3] + K[i - 2] + K[i - 1])
T = int(input())
for _ in range(T):
    n = int(input())
    print(K[n])
