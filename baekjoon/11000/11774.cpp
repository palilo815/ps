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

    vector<pair<int, int>> e(n - 1);
    for (auto& [u, v] : e) cin >> u >> v, --u, --v;

    vector<vector<int>> adj(n);
    for (const auto& [u, v] : e) {
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    vector<bool> mark(n);
    auto dfs = [&](int src) {
        vector<bool> visited(n);
        visited[src] = true;

        vector<int> stk;
        for (stk.emplace_back(src); !stk.empty();) {
            const auto u = stk.back();
            stk.pop_back();

            for (const auto& v : adj[u])
                if (!visited[v]) {
                    visited[v] = true;
                    mark[v] = !mark[u];
                    stk.emplace_back(v);
                }
        }
    };
    dfs(0);

    for (const auto& [u, v] : e)
        cout << (mark[u]) << '\n';
}