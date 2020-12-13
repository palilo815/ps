#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e5;
const int mxM = 2e5;

struct edge {
    int u, v, w, i;
};
struct disjoint_set {
    vector<int> par;
    disjoint_set(int n) {
        par.resize(n, -1);
    }
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

edge e[mxM];
vector<pair<int, int>> adj[mxN];
bitset<mxM> used;
int par[mxN], dep[mxN], link[mxN], ans[mxM];

void dfs(int u) {
    for (auto& [v, i] : adj[u])
        if (v != par[u]) {
            par[v] = u, dep[v] = dep[u] + 1, link[v] = i;
            dfs(v);
        }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; ++i) {
        cin >> e[i].u >> e[i].v >> e[i].w;
        --e[i].u, --e[i].v, e[i].i = i;
    }

    sort(e, e + m, [&](auto& a, auto& b) {
        return a.w < b.w;
    });

    int64_t mst = 0;
    disjoint_set dsu(n);
    for (int i = 0; i < m; ++i)
        if (dsu.merge(e[i].u, e[i].v)) {
            mst += e[i].w;
            used[i] = true;
            adj[e[i].u].emplace_back(e[i].v, i);
            adj[e[i].v].emplace_back(e[i].u, i);
        }

    dfs(0);

    memset(ans, -1, sizeof(int) * m);
    dsu.reset();
    for (int i = 0; i < m; ++i) {
        if (used[i]) continue;
        ans[e[i].i] = 0;
        int u = dsu.find(e[i].u), v = dsu.find(e[i].v);
        while (u != v) {
            if (dep[u] > dep[v])
                u = dsu.find(par[u]);
            else if (dep[u] < dep[v])
                v = dsu.find(par[v]);
            else
                u = dsu.find(par[u]), v = dsu.find(par[v]);
        }

        int lca = u, p;
        for (u = dsu.find(e[i].u); u != lca; u = p) {
            p = dsu.find(par[u]);
            dsu.par[u] = lca;
            ans[e[link[u]].i] = e[i].w - e[link[u]].w;
        }
        for (v = dsu.find(e[i].v); v != lca; v = p) {
            p = dsu.find(par[v]);
            dsu.par[v] = lca;
            ans[e[link[v]].i] = e[i].w - e[link[v]].w;
        }
    }

    for (int i = 0; i < m; ++i)
        cout << (ans[i] == -1 ? -1 : mst + ans[i]) << '\n';
}