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

    vector<vector<pair<int, int>>> adj(n);
    for (int i = n - 1, u, v, w; i--;) {
        cin >> u >> v >> w, --u, --v;
        adj[u].emplace_back(w, v);
        adj[v].emplace_back(w, u);
    }

    vector<int> idx;
    idx.reserve(n);
    auto dfs = [&](int src) {
        vector<bool> visited(n);
        visited[src] = true;

        vector<int> stk;
        for (stk.emplace_back(src); !stk.empty();) {
            const auto u = stk.back();
            stk.pop_back();

            idx.emplace_back(u);
            for (const auto& [w, v] : adj[u])
                if (!visited[v]) {
                    visited[v] = true;
                    stk.emplace_back(v);
                }
        }
    };
    dfs(0);

    int64_t d = 0;
    vector<int> sz(n);
    for (int i = n; i--;) {
        const auto& u = idx[i];
        sz[u] = 1;
        for (const auto& [w, v] : adj[u])
            if (sz[v]) {
                sz[u] += sz[v];
                d += int64_t(w) * sz[v];
            }
    }

    vector<int64_t> ans(n);
    ans[0] = d;

    for (const auto& u : idx)
        for (const auto& [w, v] : adj[u])
            if (!ans[v])
                ans[v] = ans[u] + int64_t(w) * (n - (sz[v] << 1));

    for (const auto& x : ans)
        cout << x << '\n';
}