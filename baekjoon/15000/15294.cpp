#include <bits/stdc++.h>
using namespace std;

struct query {
    int u, v, lca, len;
};

struct disjoint_set {
    vector<int> par;
    disjoint_set(int n) : par(n, -1) {}
    int find(int u) {
        return par[u] < 0 ? u : par[u] = find(par[u]);
    }
    void merge(int u, int v) {
        par[v] = u;
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, f;
    cin >> n >> f;

    vector<vector<int>> adj(n);
    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v, --u, --v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    vector<int> par(n), sz(n), top(n), in(n), dep(n);
    int t = 0;
    function<void(int)> dfs = [&](int u) {
        sz[u] = 1;
        for (auto& v : adj[u]) {
            if (v == par[u]) continue;
            par[v] = u, dep[v] = dep[u] + 1;
            dfs(v);
            sz[u] += sz[v];
            if (adj[u][0] == par[u] || sz[v] > sz[adj[u][0]])
                swap(v, adj[u][0]);
        }
    };
    function<void(int)> hld = [&](int u) {
        in[u] = t++;
        for (const auto& v : adj[u]) {
            if (v == par[u]) continue;
            top[v] = v == adj[u][0] ? top[u] : v;
            hld(v);
        }
    };
    dfs(0);
    hld(0);

    auto get_lca = [&](int u, int v) {
        for (; top[u] != top[v]; u = par[top[u]])
            if (sz[top[u]] > sz[top[v]])
                swap(u, v);
        return in[u] < in[v] ? u : v;
    };

    vector<query> q(f);
    for (auto& [u, v, lca, len] : q) {
        cin >> u >> v, --u, --v;
        lca = get_lca(u, v);
        len = dep[u] + dep[v] - (dep[lca] << 1);
    }
    sort(q.begin(), q.end(), [&](auto& a, auto& b) {
        return a.len < b.len;
    });

    disjoint_set dsu(n);
    vector<int> cnt(n);
    auto laminar = [&](int u, int lca) {
        for (u = dsu.find(u); dep[u] > dep[lca]; u = dsu.find(u)) {
            if (cnt[u] == 2 || cnt[par[u]] == 2) return false;
            ++cnt[u], ++cnt[par[u]];
            dsu.merge(par[u], u);
        }
        return true;
    };

    for (const auto& [u, v, lca, _] : q) {
        if (!laminar(u, lca) || !laminar(v, lca) || cnt[u] == 2 || cnt[v] == 2)
            return cout << "No", 0;
    }
    cout << "Yes";
}