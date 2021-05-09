#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    constexpr int mod = 1e9 + 7;
    auto inv = [&](int64_t x) {
        int64_t ret = 1;
        for (int p = mod - 2; p; p >>= 1) {
            if (p & 1) ret = ret * x % mod;
            x = x * x % mod;
        }
        return ret;
    };

    int n;
    cin >> n;

    int ans = 0;
    for (int x, y; n--;) {
        cin >> x >> y;
        ans += inv(x) * y % mod;
        ans %= mod;
    }
    cout << ans;
}