#include <cstdio>

char s[50001];

int main() {
    scanf("%s", s);
    int ans = 0;
    for (int i = 0, x = 0; s[i + 1]; ++i)
        if (s[i] == s[i + 1])
            s[i] == '(' ? ++x : ans += x;
    printf("%d", ans);
    return 0;
}