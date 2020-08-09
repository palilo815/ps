#include <cstdio>

char s[2001];

int main() {
    for (int t = 1;; ++t) {
        scanf("%s", s);
        if (s[0] == '-') break;

        int stk = 0, ans = 0;
        for (int i = 0; s[i]; ++i) {
            if (s[i] == '{') ++stk;
            else stk ? --stk : (++ans, ++stk);
        }
        printf("%d. %d\n", t, ans + stk / 2);
    }
    return 0;
}