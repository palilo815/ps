#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n;

    vector<int> a(n + 1);
    for (auto& x : a) cin >> x, --x;

    vector<int64_t> dp(n + 1), prv(n + 1);
    dp[a[0]] = 1;

    for (int i = 1; i < n; ++i) {
        dp.swap(prv);
        fill(dp.begin(), dp.end(), 0);

        for (int j = 0; j <= n; ++j)
            if (prv[j]) {
                const auto& [mn, mx] = minmax(j, a[i]);
                if (mn < a[i + 1]) {
                    dp[mn] += prv[j];
                    if (dp[mn] >= INT_MAX) dp[mn] -= INT_MAX;
                }
                if (a[i + 1] < mx) {
                    dp[mx] += prv[j];
                    if (dp[mx] >= INT_MAX) dp[mx] -= INT_MAX;
                }
            }
    }

    int64_t ans = 0;
    for (const auto& x : dp) {
        ans += x;
        if (ans >= INT_MAX) ans -= INT_MAX;
    }
    cout << ans;
}