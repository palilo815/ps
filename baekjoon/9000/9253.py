import sys
input = sys.stdin.readline


def kmp_build(s, lps):
    n = len(s) - 1
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
    len_txt = len(txt) - 1
    len_pat = len(pat) - 1
    lps = [0] * len_pat
    kmp_build(pat, lps)
    i, j = 0, 0
    while i < len_txt:
        if pat[j] == txt[i]:
            i += 1
            j += 1
        if j == len_pat:
            return True
        elif i < len_txt and pat[j] != txt[i]:
            if j == 0:
                i += 1
            else:
                j = lps[j - 1]
    return False


a = input()
b = input()
ans = input()
if kmp_search(a, ans) and kmp_search(b, ans):
    print("YES")
else:
    print("NO")
