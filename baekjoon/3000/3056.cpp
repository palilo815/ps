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

    vector<vector<int>> a(n, vector<int>(n));
    for (auto& vt : a)
        for (auto& x : vt)
            cin >> x;

    vector<double> dp(1 << n);
    dp[0] = 1;

    for (int mask = 0; mask < 1 << n; ++mask)
        for (int i = 0; i < n; ++i)
            if (!(mask >> i & 1))
                dp[mask | (1 << i)] = max(dp[mask | (1 << i)], dp[mask] * a[__builtin_popcount(mask)][i]);

    cout << fixed << setprecision(9)
         << dp.back() / pow(100, n - 1);
}