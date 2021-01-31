#include <bits/stdc++.h>
using namespace std;

struct edge {
    int u, v, w, id;
};

struct disjoint_set {
    vector<int> par, dist;
    disjoint_set(int n) : par(n, -1), dist(n, 0x3f3f3f3f) {}
    int find(int u) {
        while (par[u] >= 0) u = par[u];
        return u;
    }
    bool merge(int u, int v, int w) {
        u = find(u), v = find(v);
        if (u == v) return false;

        if (par[u] > par[v]) swap(u, v);
        par[u] += par[v];
        par[v] = u;

        dist[v] = w;
        return true;
    }
    int query(int u, int v) {
        int ret;
        for (; u != v; u = par[u]) {
            if (dist[u] > dist[v]) swap(u, v);
            ret = dist[u];
        }
        return ret;
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
    for (int i = 0; i < m; ++i) {
        cin >> e[i].u >> e[i].v >> e[i].w;
        --e[i].u, --e[i].v, e[i].id = i;
    }

    sort(e.begin(), e.end(), [&](auto& a, auto& b) {
        return a.w < b.w;
    });

    vector<int> ans(m, -1);
    disjoint_set dsu(n);
    int64_t mst = 0;

    for (const auto& [u, v, w, id] : e)
        if (dsu.merge(u, v, w))
            mst += w, ans[id] = 0;

    for (const auto& [u, v, w, id] : e)
        if (ans[id] == -1)
            ans[id] = w - dsu.query(u, v);

    for (const auto& x : ans)
        cout << mst + x << '\n';
}