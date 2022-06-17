#include <stdio.h>
#include <string.h>

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    char s[50][51];
    for (int i = 0; i < n; ++i) {
        scanf("%s", &s[i]);
    }
    int k;
    scanf("%d", &k);
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        int zero = 0;
        for (int j = 0; j < m; ++j) {
            zero += s[i][j] == '0';
        }
        if (zero > k || (k - zero) % 2) continue;
        int res = 0;
        for (int j = 0; j < n; ++j) {
            res += strcmp(s[i], s[j]) == 0;
        }
        if (res > ans) ans = res;
    }
    printf("%d", ans);
}
