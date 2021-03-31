#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;
    assert(n - 1 == m);

    vector<vector<pair<int, int>>> adj(n);
    for (int u, v, w; m--;) {
        cin >> u >> v >> w, --u, --v;
        adj[u].emplace_back(w, v);
        adj[v].emplace_back(w, u);
    }

    vector<int> vtx(n);
    auto dfs = [&](int src) {
        vector<bool> visited(n);
        visited[src] = true;

        vector<int> stk = {src};
        for (int i = 0; i < n; ++i) {
            const auto u = stk.back();
            stk.pop_back();

            vtx[i] = u;
            for (const auto& [w, v] : adj[u])
                if (!visited[v]) {
                    visited[v] = true;
                    stk.emplace_back(v);
                }
        }
    };
    dfs(0);
    reverse(vtx.begin(), vtx.end());

    vector<int> dp(n, -1);
    for (const auto& u : vtx) {
        bool is_leaf = true;
        dp[u] = 0;
        for (const auto& [w, v] : adj[u])
            if (~dp[v]) {
                is_leaf = false;
                dp[u] += min(w, dp[v]);
            }
        if (is_leaf) dp[u] = INT_MAX;
    }

    if (n == 1) dp[0] = 0;
    cout << dp[0] << '\n';
}
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int T;
    cin >> T;
    while (T--) solve();
}