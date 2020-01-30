s = input()
if len(s) < 3:
    f = True
else:
    f = True
    gap = int(s[1]) - int(s[0])
    for i in range(2, len(s)):
        if int(s[i]) - int(s[i - 1]) != gap:
            f = False
            break
if (f):
    print("◝(⑅•ᴗ•⑅)◜..°♡ 뀌요미!!")
else:
    print("흥칫뿡!! <(￣ ﹌ ￣)>")
