basis = [90, 80, 70, 60, 0]
grade = ['A', 'B', 'C', 'D', 'F']
score = int(input())
for i in range(5):
    if score >= basis[i]:
        print(grade[i])
        break
