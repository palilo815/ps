def is_prime(num):
    i = 2
    while i * i <= num:
        if num % i == 0:
            return False
        i += 1
    return True


a, b = map(int, input().split())
prime = is_prime(a)
if prime:
    prime = is_prime(b)
if prime:
    print("Yes")
else:
    print("No")
