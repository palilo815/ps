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
    int n, m;
    cin >> n >> m;
    if (n < 3) return cout << -1, 0;
    disjoint_set dsu(n);
    vector<pair<int, pair<int, int>>> edge;
    edge.reserve(n - 1);
    vector adj(n, -1);
    for (int i = 0, u, v; i < m; ++i) {
        cin >> u >> v, --u, --v;
        if (dsu.unite(u, v)) {
            if (u > v) swap(u, v);
            edge.emplace_back(i, pair(u, v));
            adj[u] = adj[u] == -1 ? v : INT_MAX;
            adj[v] = adj[v] == -1 ? u : INT_MAX;
        }
    }
    const auto components = dsu.num_components();
    if (components > 2) return cout << -1, 0;
    if (components == 1) {
        const int leaf = find_if(adj.begin(), adj.end(), [&](const auto& x) {
            return x != INT_MAX;
        }) - adj.begin();
        const pair target(min(leaf, adj[leaf]), max(leaf, adj[leaf]));
        edge.erase(find_if(edge.begin(), edge.end(), [&](const auto& x) {
            return x.second == target;
        }));
        cout << 1 << ' ' << n - 1 << '\n';
        cout << leaf + 1 << '\n';
        cout << '\n';
        for (int i = 0; i < n; ++i) {
            if (i != leaf) {
                cout << i + 1 << ' ';
            }
        }
        cout << '\n';
        for (const auto& x : edge) {
            cout << x.first + 1 << ' ';
        }
    } else {
        if (n % 2 == 0 && dsu.size_of(0) == n / 2) {
            return cout << -1, 0;
        }
        const int group0 = dsu.find(0);
        vector<int> v0, v1;
        for (int i = 0; i < n; ++i) {
            (dsu.find(i) == group0 ? v0 : v1).emplace_back(i);
        }
        auto pivot = partition(edge.begin(), edge.end(), [&](const auto& x) {
            return dsu.find(x.second.first) == group0;
        });
        cout << v0.size() << ' ' << v1.size() << '\n';
        for (const auto& x : v0) {
            cout << x + 1 << ' ';
        }
        cout << '\n';
        for (auto it = edge.begin(); it != pivot; ++it) {
            cout << it->first + 1 << ' ';
        }
        cout << '\n';
        for (const auto& x : v1) {
            cout << x + 1 << ' ';
        }
        cout << '\n';
        for (auto it = pivot; it != edge.end(); ++it) {
            cout << it->first + 1 << ' ';
        }
    }
}