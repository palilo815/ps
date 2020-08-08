#include <cstdio>

void solve() {
    int R, C; scanf("%d%d", &R, &C);
    int s1 = 0, s2 = 0, x;
    for (int i = 0; i < R; ++i)
        for (int j = 0; j < C; ++j) {
            scanf("%d", &x);
            ((i + j) & 1 ? s1 : s2) += x;
        }
    printf("%s\n", s1 == s2 ? "YES" : "NO");
}
int main() {
    int T; scanf("%d", &T);
    while (T--) solve();
    return 0;
}