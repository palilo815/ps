#include <bits/stdc++.h>
using namespace std;

class disjoint_set {
    const int n;
    vector<int> par;

public:
    disjoint_set(int _n) : n(_n), par(n, -1) {}
    int find(int u) {
        return par[u] < 0 ? u : par[u] = find(par[u]);
    }
    bool unite(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) {
            return false;
        }
        if (par[u] > par[v]) {
            swap(u, v);
        }
        par[u] += par[v];
        par[v] = u;
        return true;
    }
    int size_of(int u) { return -par[find(u)]; }
    bool is_same(int u, int v) { return find(u) == find(v); }
    int num_components() const {
        return count_if(par.begin(), par.end(), [&](auto& x) { return x < 0; });
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
    vector<int> a(n);
    for (auto& x : a) {
        cin >> x;
    }
    vector<tuple<int, int, int>> edges(m);
    for (auto& [u, v, w] : edges) {
        cin >> u >> v >> w, --u, --v;
        w += w + a[u] + a[v];
    }
    sort(edges.begin(), edges.end(), [&](const auto& lhs, const auto& rhs) {
        return get<2>(lhs) < get<2>(rhs);
    });
    disjoint_set dsu(n);
    int ans = *min_element(a.begin(), a.end());
    for (const auto& [u, v, w] : edges) {
        if (dsu.unite(u, v)) {
            ans += w;
        }
    }
    cout << ans;
}