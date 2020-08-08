#include <cstdio>
#include <cstring>

const int mx = 400;

char bulb[mx + 1], tr[mx], tc[mx];

void solve() {
    int R, C; scanf("%d%d", &R, &C); getchar();
    memset(tr, 0, R);
    memset(tc, 0, C);

    int ans = 0;
    for (int i = 0; i < R; ++i) {
        scanf("%s", bulb);
        for (int j = C - 1; ~j; --j)
            if ((bulb[j] - '0' + tr[i] + tc[j]) % 2 == 0)
                ++ans, tr[i] ^= 1, tc[j] ^= 1;
    }
    printf("%d\n", ans);
}
int main() {
    int T; scanf("%d", &T);
    while (T--) solve();
    return 0;
}