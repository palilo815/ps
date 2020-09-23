#include <cstdio>

int main() {
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int K, N;
    scanf("%d%d", &K, &N);

    for (int x; N--;) {
        scanf("%d", &x);
        int ans = 0, i = 1, d = K;
        while (d >= i && i < x) {
            d -= i++;
            ++ans;
        }
        while (d >= i << 1) {
            d -= i++ << 1;
            ans += 2;
        }
        if (d) ++ans;
        if (d > i) ++ans;
        printf("%d\n", ans);
    }
    return 0;
}