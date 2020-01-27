import decimal

a, b = input().split()
decimal.getcontext().prec = 10000
print("{0:f}".format(decimal.Decimal(a) ** int(b)))
