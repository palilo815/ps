latin = {
    "a": "as",
    "i": "ios",
    "y": "ios",
    "l": "les",
    "n": "anes",
    "o": "os",
    "r": "res",
    "t": "tas",
    "u": "us",
    "v": "ves",
    "w": "was"
}

for _ in range(int(input())):
    word = input()
    if len(word) > 1 and word[-1] == 'e' and word[-2] == 'n':
        word = word[:-1]
    last = word[-1:]
    word = word[:-1] + latin.get(last, last + "us")
    print(word)
