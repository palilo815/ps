#include <cstdio>
#include <cmath>
typedef long long ll;

int main() {
    ll x, y; scanf("%lld %lld", &x, &y);
    ll s = x + y;
    ll i = (ll)(sqrt(s) + 1e-9);

    if (i * i != s) {
        printf("-1");
        return 0;
    }

    i = 2 * i - 1;
    int ans = 0;
    while (x) {
        if (i < 0) { ans = -1; break; }
        if (x < i) {
            i = x;
            if (!(i & 1)) --i;
            x -= i;
            ++ans;
        }
        else if (x - i != 2) {
            x -= i;
            ++ans;
        }
        i -= 2;
    }
    printf("%d", ans);
    return 0;
}