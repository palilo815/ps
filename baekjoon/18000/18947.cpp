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
    for (int i = 1, u, v, w; i < n; ++i) {
        cin >> u >> v >> w, --u, --v;
        adj[u].emplace_back(w, v);
        adj[v].emplace_back(w, u);
    }

    vector<int> par(n), sz(n), top(n), in(n);
    vector<int64_t> f(n);
    int t = 0;
    function<void(int)> dfs = [&](int u) {
        sz[u] = 1;
        for (auto& [w, v] : adj[u]) {
            if (v == par[u]) continue;
            par[v] = u;
            dfs(v);
            sz[u] += sz[v];
            if (adj[u][0].second == par[u] || sz[v] > sz[adj[u][0].second]) {
                swap(w, adj[u][0].first);
                swap(v, adj[u][0].second);
            }
        }
    };
    function<void(int)> hld = [&](int u) {
        in[u] = t++;
        for (const auto& [w, v] : adj[u]) {
            if (v == par[u]) continue;
            top[v] = v == adj[u][0].second ? top[u] : v;
            f[v] = f[u] + w;
            hld(v);
        }
    };
    dfs(0);
    hld(0);

    auto lca = [&](int u, int v) {
        for (; top[u] != top[v]; u = par[top[u]])
            if (sz[top[u]] > sz[top[v]])
                swap(u, v);
        return in[u] < in[v] ? u : v;
    };

    auto cmp = [&](int a, int b) { return in[a] < in[b]; };
    set<int, decltype(cmp)> red_nodes(cmp);

    int64_t ans = 0;
    auto add = [&](int u) {
        ans += f[u];
        auto it = red_nodes.emplace(u).first;
        if (red_nodes.size() == 1) return;

        auto a = it == red_nodes.begin() ? *red_nodes.rbegin() : *prev(it);
        auto b = ++it == red_nodes.end() ? *red_nodes.begin() : *it;
        if (a != b) ans += f[lca(a, b)];
        ans -= f[lca(a, u)] + f[lca(b, u)];
    };
    auto rem = [&](int u) {
        ans -= f[u];
        auto it = red_nodes.erase(red_nodes.find(u));
        if (red_nodes.empty()) return;

        auto a = it == red_nodes.begin() ? *red_nodes.rbegin() : *prev(it);
        auto b = it == red_nodes.end() ? *red_nodes.begin() : *it;
        if (a != b) ans -= f[lca(a, b)];
        ans += f[lca(a, u)] + f[lca(b, u)];
    };

    int q;
    cin >> q;

    char op;
    for (int u; q--;) {
        cin >> op >> u, --u;
        op == '+' ? add(u) : rem(u);
        cout << (red_nodes.size() <= 1 ? 0 : ans) << '\n';
    }
}