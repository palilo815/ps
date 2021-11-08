#include <bits/stdc++.h>
using namespace std;

class disjoint_set {
    const size_t n;
    vector<int> par;

public:
    disjoint_set(size_t n) : n(n), par(n, -1) {}

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
    int n, m, k;
    cin >> n >> m >> k;
    disjoint_set dsu(n);
    for (int u, v, i = k - 1; i--;) {
        cin >> u >> v, --u, --v;
        dsu.unite(u, v);
    }
    cin.ignore();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    for (int u, v, i = m - k; i--;) {
        cin >> u >> v, --u, --v;
        dsu.unite(u, v);
    }
    const int64_t x = dsu.size_of(0);
    cout << x * (n - x);
}