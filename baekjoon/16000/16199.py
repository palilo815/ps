born = list(map(int, input().split()))
die = list(map(int, input().split()))
age = []
for i in range(3):
    age.append(die[i] - born[i])
if age[2] < 0:
    age[1] -= 1
if age[1] < 0:
    age[0] -= 1
print(age[0], die[0] - born[0] + 1, die[0] - born[0])
