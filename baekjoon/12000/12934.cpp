#include <cstdio>
#include <cmath>
typedef long long ll;

int main() {
    ll x, y; scanf("%lld %lld", &x, &y);
    ll s = (x + y) * 2;
    ll i = (ll)(sqrt(s) + 1e-9);

    if (i * (i + 1) != s) {
        printf("-1");
        return 0;
    }

    int ans = 0;
    while (x) {
        x < i ? (x = 0) : (x -= i);
        --i, ++ans;
    }
    printf("%d", ans);
    return 0;
}