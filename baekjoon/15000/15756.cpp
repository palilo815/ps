#include <bits/stdc++.h>
using namespace std;

const int mxN = 5e4;

struct path {
    int u, v, w;
};
struct disjoint_set {
    vector<int> par;
    disjoint_set(int n) {
        par = vector<int>(n, -1);
    }
    int find(int u) {
        return par[u] == -1 ? u : par[u] = find(par[u]);
    }
    void merge(int u, int v) {
        u = find(u), v = find(v);
        if (u != v) par[v] = u;
    }
};

pair<int, int> e[mxN - 1];
vector<int> adj[mxN + 1];
int par[mxN + 1], dep[mxN + 1], ans[mxN + 1];
path q[mxN];

void dfs(int u) {
    for (int& v : adj[u])
        if (v != par[u]) {
            par[v] = u, dep[v] = dep[u] + 1;
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
    int N, M;
    cin >> N >> M;

    for (int i = 0; i < N - 1; ++i) {
        cin >> e[i].first >> e[i].second;
        adj[e[i].first].emplace_back(e[i].second);
        adj[e[i].second].emplace_back(e[i].first);
    }

    dfs(1);

    for (int i = 0; i < M; ++i)
        cin >> q[i].u >> q[i].v >> q[i].w;

    sort(q, q + M, [&](auto& a, auto& b) {
        return a.w < b.w;
    });

    memset(ans + 1, -1, sizeof(int) * N);
    disjoint_set dsu(N + 1);

    for (int i = 0; i < M; ++i) {
        auto [u, v, w] = q[i];
        u = dsu.find(u), v = dsu.find(v);
        while (u != v) {
            if (dep[u] > dep[v])
                u = dsu.find(par[u]);
            else if (dep[u] < dep[v])
                v = dsu.find(par[v]);
            else
                u = dsu.find(par[u]), v = dsu.find(par[v]);
        }

        int lca = u, p;
        for (u = dsu.find(q[i].u); u != lca; u = p) {
            p = dsu.find(par[u]);
            dsu.par[u] = lca;
            if (ans[u] == -1) ans[u] = q[i].w;
        }
        for (v = dsu.find(q[i].v); v != lca; v = p) {
            p = dsu.find(par[v]);
            dsu.par[v] = lca;
            if (ans[v] == -1) ans[v] = q[i].w;
        }
    }

    for (int i = 0; i < N - 1; ++i)
        cout << ans[par[e[i].first] == e[i].second ? e[i].first : e[i].second] << '\n';
}