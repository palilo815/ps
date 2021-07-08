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
    vector adj(n, vector<char>(n));
    for (auto& vt : adj) {
        for (auto& x : vt) {
            cin >> x;
        }
    }
    disjoint_set dsu(n);
    vector<int> cnt(n);
    for (int u = 0; u < n - 1; ++u) {
        for (int v = u + 1; v < n; ++v) {
            if (adj[u][v] == 'Y' && dsu.unite(u, v)) {
                adj[u][v] = 'N';
                ++cnt[u], ++cnt[v], --m;
            }
        }
    }
    if (dsu.num_components() != 1) {
        return cout << -1, 0;
    }
    for (int u = 0; u < n - 1; ++u) {
        for (int v = u + 1; v < n; ++v) {
            if (m && adj[u][v] == 'Y') {
                ++cnt[u], ++cnt[v], --m;
            }
        }
    }
    if (m) {
        cout << -1;
    } else {
        for (const auto& x : cnt) {
            cout << x << ' ';
        }
    }
}