#include <bits/stdc++.h>
using namespace std;

template <typename T, typename F = less<T>>
class disjoint_set {
    const T e = 0x3f3f3f3f;
    const F cmp {};
    const int n;
    vector<int> par;
    vector<T> weight;

public:
    disjoint_set(int n) : n(n), par(n, -1), weight(n, e) {}
    int find(int u) {
        while (par[u] >= 0) u = par[u];
        return u;
    }
    bool unite(int u, int v, T w) {
        u = find(u), v = find(v);
        if (u == v) return false;
        if (par[u] > par[v]) swap(u, v);
        par[u] += par[v];
        par[v] = u;
        weight[v] = w;
        return true;
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
    int n, m;
    cin >> n >> m;
    vector<tuple<int, int, int>> e(m);
    for (auto& [u, v, w] : e) {
        cin >> u >> v >> w, --u, --v;
    }
    sort(e.begin(), e.end(), [&](const auto& lhs, const auto& rhs) {
        return get<2>(lhs) < get<2>(rhs);
    });
    disjoint_set<int> dsu(n);
    int mst = 0;
    for (const auto& [u, v, w] : e) {
        if (dsu.unite(u, v, w)) mst += w;
    }
    cin >> m;
    for (int u, v; m--;) {
        cin >> u >> v, --u, --v;
        cout << mst - dsu.query(u, v) << '\n';
    }
}