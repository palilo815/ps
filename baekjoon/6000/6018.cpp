#include <bits/stdc++.h>
using namespace std;

class disjoint_set {
    vector<int> par;

public:
    disjoint_set(size_t n) : par(n, -1) {}

    int find(size_t u) {
        return par[u] < 0 ? u : par[u] = find(par[u]);
    }
    bool unite(size_t u, size_t v) {
        u = find(u), v = find(v);
        if (u == v) return false;
        if (par[u] > par[v]) swap(u, v);
        par[u] += par[v];
        par[v] = u;
        return true;
    }
    int size_of(size_t u) { return -par[find(u)]; }
    bool are_same(size_t u, size_t v) { return find(u) == find(v); }
    int num_components() const {
        return count_if(par.begin(), par.end(), [&](const auto& x) { return x < 0; });
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, m, q;
    cin >> n >> m >> q;
    disjoint_set dsu(n);
    for (int u, v; m--;) {
        cin >> u >> v, --u, --v;
        dsu.unite(u, v);
    }
    for (int u, v; q--;) {
        cin >> u >> v, --u, --v;
        cout << (dsu.are_same(u, v) ? 'Y' : 'N') << '\n';
    }
}