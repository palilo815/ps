cipher = input()
key = input()
msg = []
for i in range(min(len(key), len(cipher))):
    msg.append(chr(65 + ord(cipher[i]) - ord(key[i])))
    if msg[i] < 'A':
        msg[i] = chr(ord(msg[i]) + 26)
for i in range(len(key), len(cipher)):
    msg.append(chr(65 + ord(cipher[i]) - ord(msg[i - len(key)])))
    if msg[i] < 'A':
        msg[i] = chr(ord(msg[i]) + 26)
for x in msg:
    print(x, end="")
