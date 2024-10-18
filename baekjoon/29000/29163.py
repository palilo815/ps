n = int(input())
odd = sum(map(lambda x: int(x) % 2, input().split()))
print("Happy" if odd < n - odd else "Sad")
