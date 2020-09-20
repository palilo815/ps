#include <cstdio>
using ll = long long;

int main() {
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N, K;
    scanf("%d%d", &N, &K);

    ll ans = 0;
    for (int i = 0; K; ++i) {
        if (N & (1LL << i)) continue;
        if (K & 1) ans |= (1LL << i);
        K >>= 1;
    }
    printf("%lld", ans);
    return 0;
}