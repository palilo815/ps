#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, m;
    cin >> n >> m;

    vector<vector<int>> a(m, vector<int>(n));
    for (auto& vt : a)
        for (auto& x : vt)
            cin >> x;

    if (m == 1)
        return cout << a[0][0] + accumulate(a[0].begin() + 1, a[0].end(), 0, [&](auto& a, auto& b) { return a + (b >> 1); }), 0;

    vector<int> dp(m), prv(m);
    for (int i = 0; i < n; ++i) {
        dp.swap(prv);
        for (int j = 0; j < m; ++j) {
            int mx = -1;
            for (int k = 0; k < m; ++k)
                mx = max(mx, prv[k] + (j == k ? a[j][i] / 2 : a[j][i]));
            dp[j] = mx;
        }
    }
    cout << *max_element(dp.begin(), dp.end());
}