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

    vector<int> cur(n), prv(n), dp(n);

    for (auto& x : cur) cin >> x;
    for (int i = 1; i < n; ++i)
        dp[i] = dp[i - 1] + max(0, cur[i] - cur[i - 1] + 1);

    for (int t = 1; t < n; ++t) {
        cur.swap(prv);
        for (auto& x : cur) cin >> x;

        if (prv[0] <= cur[0]) dp[0] += cur[0] - prv[0] + 1;
        for (int i = 1; i < n; ++i)
            dp[i] = min(dp[i - 1] + max(0, cur[i] - cur[i - 1] + 1), dp[i] + max(0, cur[i] - prv[i] + 1));
    }
    cout << dp.back();
}