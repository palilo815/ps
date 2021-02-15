#include <bits/stdc++.h>
using namespace std;

struct edge {
    int u, v, w;
};

struct disjoint_set {
    vector<int> par, dist;
    disjoint_set(int n) : par(n, -1), dist(n) {}
    int find(int u) {
        return par[u] < 0 ? u : par[u] = find(par[u]);
    }
    void merge(int u, int v, int w) {
        u = find(u), v = find(v);
        if (u == v) return;

        if (par[u] > par[v]) swap(u, v);
        par[u] += par[v];
        par[v] = u;
        dist[v] = w;
    }
    int query(int u, int v) {
        int ret;
        for (; u != v; u = par[u]) {
            if (dist[u] < dist[v]) swap(u, v);
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
    for (auto& [u, v, w] : e)
        cin >> u >> v >> w, --u, --v;

    sort(e.begin(), e.end(), [&](auto& a, auto& b) {
        return a.w > b.w;
    });

    disjoint_set dsu(n);
    for (const auto& [u, v, w] : e)
        dsu.merge(u, v, w);

    int u, v;
    cin >> u >> v, --u, --v;
    cout << dsu.query(u, v) << '\n';
}