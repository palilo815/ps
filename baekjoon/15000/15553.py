input = __import__('sys').stdin.readline

N, K = map(int, input().split())
s = int(input())
time, prev, curr = [], s, s

for i in range(N - 1):
    curr = int(input())
    time.append(curr - prev - 1)
    prev = curr

time.sort(reverse=True)
print(curr + 1 - s - sum(time[:K-1]))
