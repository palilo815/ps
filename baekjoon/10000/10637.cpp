#include <bits/stdc++.h>
using namespace std;

struct edge {
    int u, v, id;
};

struct disjoint_set {
    vector<int> par;
    disjoint_set(int n) : par(n, -1) {}
    void reset() {
        fill(par.begin(), par.end(), -1);
    }
    int find(int u) {
        return par[u] < 0 ? u : par[u] = find(par[u]);
    }
    bool merge(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) return false;

        if (par[u] > par[v]) swap(u, v);
        par[u] += par[v];
        par[v] = u;
        return true;
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, m;
    cin >> n >> m;

    vector<edge> e(m);
    vector<int> weight(m);
    for (int i = 0; i < m; ++i) {
        cin >> e[i].u >> e[i].v >> weight[i];
        --e[i].u, --e[i].v, e[i].id = i;
    }

    sort(e.begin(), e.end(), [&](auto& a, auto& b) {
        return weight[a.id] < weight[b.id];
    });

    vector<vector<pair<int, int>>> adj(n);
    vector<int> ans(m, -1);
    disjoint_set dsu(n);
    int64_t mst = 0;

    for (const auto [u, v, id] : e)
        if (dsu.merge(u, v)) {
            mst += weight[id];
            adj[u].emplace_back(id, v);
            adj[v].emplace_back(id, u);
        } else
            ans[id] = 0;

    vector<int> par(n), dep(n), holding_edge(n);
    auto dfs = [&](auto self, int u) -> void {
        for (auto& [id, v] : adj[u])
            if (v != par[u]) {
                par[v] = u, dep[v] = dep[u] + 1, holding_edge[v] = id;
                self(self, v);
            }
    };
    dfs(dfs, 0);

    dsu.reset();
    for (auto [u, v, id] : e) {
        if (ans[id] == -1) continue;

        const int u0 = dsu.find(u), v0 = dsu.find(v);
        for (u = u0, v = v0; u != v; u = dsu.find(par[u]))
            if (dep[u] < dep[v])
                swap(u, v);

        int lca = u, p;
        for (u = u0; u != lca; u = p) {
            p = dsu.find(par[u]);
            dsu.par[u] = lca;
            if (ans[holding_edge[u]] == -1)
                ans[holding_edge[u]] = weight[id] - weight[holding_edge[u]];
        }
        for (v = v0; v != lca; v = p) {
            p = dsu.find(par[v]);
            dsu.par[v] = lca;
            if (ans[holding_edge[v]] == -1)
                ans[holding_edge[v]] = weight[id] - weight[holding_edge[v]];
        }
    }

    for (int& x : ans)
        cout << (x == -1 ? -1 : mst + x) << '\n';
}