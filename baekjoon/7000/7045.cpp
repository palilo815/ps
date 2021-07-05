#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n;
    vector<vector<int>> adj(n);
    for (int u, v, i = n - 1; i--;) {
        cin >> u >> v, --u, --v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    auto sz = [&](int root) -> vector<int> {
        vector<int> rev_dfn(n), stk = {root};
        for (int i = n; i--;) {
            const auto u = stk.back();
            stk.pop_back();
            rev_dfn[i] = u;
            for (const auto& v : adj[u]) {
                adj[v].erase(find(adj[v].begin(), adj[v].end(), u));
                stk.emplace_back(v);
            }
        }
        vector sz(n, 1);
        for (const auto& u : rev_dfn) {
            for (const auto& v : adj[u]) {
                sz[u] += sz[v];
            }
        }
        return sz;
    }(0);
    vector<bool> is_centroid(n);
    for (int u = 0; u < n; ++u) {
        if (n - sz[u] <= n / 2 && all_of(adj[u].begin(), adj[u].end(), [&](const auto& v) { return sz[v] <= n / 2; })) {
            is_centroid[u] = true;
        }
    }
    for (int i = 0; i < n; ++i) {
        if (is_centroid[i]) {
            cout << i + 1 << '\n';
        }
    }
}