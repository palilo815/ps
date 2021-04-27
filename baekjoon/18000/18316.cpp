#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, m, c;
    cin >> n >> m >> c;

    vector<int> mooney(n);
    for (auto& x : mooney) cin >> x;

    vector<vector<int>> adj(n);
    for (int u, v; m--;) {
        cin >> u >> v, --u, --v;
        adj[u].emplace_back(v);
    }

    vector<int> dp(n, -1), prv(n);
    dp[0] = 0;

    int ans = 0;
    for (int t = 1; t <= 1000; ++t) {
        dp.swap(prv);
        fill(dp.begin(), dp.end(), -1);

        for (int u = 0; u < n; ++u) {
            if (prv[u] == -1) continue;
            for (const auto& v : adj[u])
                dp[v] = max(dp[v], prv[u] + mooney[v]);
        }
        ans = max(ans, dp[0] - c * t * t);
    }
    cout << ans;
}