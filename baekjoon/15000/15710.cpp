#include <cstdio>
using ll = long long;

const int mod = 1e9 + 7;

int main() {
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int a, b, n;
    scanf("%d%d%d", &a, &b, &n);

    ll p = 31LL * (n - 1);
    int ans = 1, x = 2;
    while (p) {
        if (p & 1) ans = (ll)ans * x % mod;
        x = (ll)x * x % mod;
        p >>= 1;
    }
    printf("%d", ans);
    return 0;
}