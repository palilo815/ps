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
    int num_components() {
        return count_if(par.begin(), par.end(), [&](auto& x) { return x < 0; });
    }
};

void solve() {
    int n;
    cin >> n;

    disjoint_set dsu(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            char c;
            cin >> c;
            if (c == '1')
                dsu.unite(i, j);
        }
    }

    cout << n - dsu.num_components() << '\n';
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    int T;
    cin >> T;
    while (T--) solve();
}