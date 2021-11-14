#include <bits/stdc++.h>
using namespace std;

template <typename T, typename F = less<T>>
class disjoint_set {
    // change this (1/1)
    const T e = {};
    const F cmp {};
    // change this (1/1)
    const int n;
    vector<int> par;
    vector<T> weight;

public:
    disjoint_set(int n) : n(n), par(n, -1), weight(n, e) {}
    int find(int u) {
        while (par[u] >= 0) u = par[u];
        return u;
    }
    void unite(int u, int v, T w) {
        u = find(u), v = find(v);
        if (u == v) return;
        if (par[u] > par[v]) swap(u, v);
        par[u] += par[v];
        par[v] = u;
        weight[v] = w;
    }
    T query(int u, int v) {
        T ret = e;
        for (; u != v; u = par[u]) {
            if (cmp(weight[v], weight[u])) swap(u, v);
            ret = weight[u];
        }
        return ret;
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, m, k;
    cin >> n >> m >> k;
    disjoint_set<int, greater<int>> dsu(n);
    vector<tuple<int, int, int>> e(m);
    for (auto& [u, v, w] : e) {
        cin >> u >> v >> w, --u, --v;
    }
    sort(e.begin(), e.end(), [&](const auto& lhs, const auto& rhs) {
        return get<2>(lhs) > get<2>(rhs);
    });
    for (const auto& [u, v, w] : e) {
        dsu.unite(u, v, w);
    }
    for (int u, v; k--;) {
        cin >> u >> v, --u, --v;
        cout << dsu.query(u, v) << '\n';
    }
}