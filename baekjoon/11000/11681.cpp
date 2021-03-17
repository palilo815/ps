#include <bits/stdc++.h>
using namespace std;

constexpr auto mod = 2147483647u;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    unsigned n;
    cin >> n;

    vector<unsigned> a(n + 1);
    for (auto& x : a) cin >> x, --x;

    vector<unsigned> dp(n + 1), prv(n + 1);
    dp[a[0]] = 1;

    for (unsigned i = 1; i < n; ++i) {
        dp.swap(prv);
        fill(dp.begin(), dp.end(), 0);

        for (unsigned j = 0; j <= n; ++j)
            if (prv[j]) {
                const auto& [mn, mx] = minmax(j, a[i]);
                if (mn < a[i + 1]) {
                    dp[mn] += prv[j];
                    if (dp[mn] >= mod) dp[mn] -= mod;
                }
                if (a[i + 1] < mx) {
                    dp[mx] += prv[j];
                    if (dp[mx] >= mod) dp[mx] -= mod;
                }
            }
    }

    unsigned ans = 0;
    for (const auto& x : dp) {
        ans += x;
        if (ans >= mod) ans -= mod;
    }
    cout << ans;
}