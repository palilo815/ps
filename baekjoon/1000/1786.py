def kmp_build(s, lps):
    n = len(s)
    lps[0] = 0
    j, i = 0, 1
    while i < n:
        if s[i] == s[j]:
            j += 1
            lps[i] = j
            i += 1
        else:
            if j == 0:
                lps[i] = 0
                i += 1
            else:
                j = lps[j - 1]


def kmp_search(txt, pat):
    ret = []
    len_txt = len(txt)
    len_pat = len(pat)
    lps = [None] * len_pat
    kmp_build(pat, lps)
    i, j = 0, 0
    while i < len_txt:
        if pat[j] == txt[i]:
            i += 1
            j += 1
        if j == len_pat:
            ret.append(i - j + 1)
            j = lps[j - 1]
        elif i < len_txt and pat[j] != txt[i]:
            if j == 0:
                i += 1
            else:
                j = lps[j - 1]
    return ret


txt = input()
pat = input()
ans = kmp_search(txt, pat)
print(len(ans))
for i in ans:
    print(i)
