#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int64_t x, y, w, s;
    cin >> x >> y >> w >> s;
    int64_t ans = 0;
    if (s < w * 2) {
        ans += s * min(x, y);
        x = abs(x - exchange(y, 0));
    }
    x += y;
    if (s < w) {
        ans += s * 2 * (exchange(x, x & 1) / 2);
    }
    ans += w * x;
    cout << ans;
}