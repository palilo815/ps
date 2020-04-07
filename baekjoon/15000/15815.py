stack = []
s = input()
for c in s:
    if '0' <= c <= '9':
        stack.append(int(c))
    else:
        a, b = stack[-2], stack[-1]
        del stack[-2:]
        if c == '+':
            stack.append(a + b)
        elif c == '-':
            stack.append(a - b)
        elif c == '*':
            stack.append(a * b)
        else:
            stack.append(a // b)
print(stack[0])
