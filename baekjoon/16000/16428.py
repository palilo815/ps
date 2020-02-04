A, B = map(int, input().split())
quo = A // B
rem = A % B
if rem < 0:
    rem += abs(B)
    quo -= B // abs(B)
print(quo)
print(rem)
