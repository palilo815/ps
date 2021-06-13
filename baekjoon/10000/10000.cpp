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
        if (u == v) return false;

        if (par[u] > par[v]) swap(u, v);
        par[u] += par[v];
        par[v] = u;
        return true;
    }
    int size_of(int u) { return -par[find(u)]; }
    bool is_same(int u, int v) { return find(u) == find(v); }
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

    int n;
    cin >> n;

    vector<int> a(n << 1);
    for (int i = 0, x, r; i < n << 1; i += 2) {
        cin >> x >> r;
        a[i] = x - r, a[i | 1] = x + r;
    }

    auto ord = a;
    sort(ord.begin(), ord.end());
    ord.erase(unique(ord.begin(), ord.end()), ord.end());

    for (auto& x : a)
        x = lower_bound(ord.begin(), ord.end(), x) - ord.begin();

    disjoint_set dsu(ord.size());

    for (int i = 0; i < n << 1; i += 2)
        dsu.unite(a[i], a[i | 1]);

    cout << 1 - ord.size() + n * 2 + dsu.num_components();
}