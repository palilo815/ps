#include <cstdio>

int main() {
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    char s[501];
    scanf("%s", s);

    int cnt0 = 0, cnt1 = 0;
    for (int i = 0; s[i]; ++i)
        s[i] == '0' ? ++cnt0 : ++cnt1;

    cnt0 >>= 1, cnt1 >>= 1;
    for (int i = 0; s[i]; ++i)
        if (s[i] == '0') {
            if (cnt0) --cnt0, putchar('0');
        } else
            cnt1 ? --cnt1 : putchar('1');
}