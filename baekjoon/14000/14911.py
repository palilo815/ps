arr = list(map(int, input().split()))
key = int(input())
arr.sort()
L = len(arr)
ans = 0
prev_a, prev_b = 0, 0
for i in range(L - 1):
    for j in range(i + 1, L):
        if arr[i] + arr[j] == key:
            if arr[i] == prev_a and arr[j] == prev_b:
                continue
            print(arr[i], arr[j])
            prev_a, prev_b = arr[i], arr[j]
            ans += 1
print(ans)
