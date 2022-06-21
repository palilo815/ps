#include <bits/stdc++.h>

class DisjointSet {
    std::vector<int> par;

public:
    DisjointSet(size_t n) : par(n, -1) {}

    int find(int u) {
        return par[u] < 0 ? u : par[u] = find(par[u]);
    }
    bool unite(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) return false;
        if (par[u] > par[v]) std::swap(u, v);
        par[u] += par[v];
        par[v] = u;
        return true;
    }
    [[nodiscard]]
    double solve() const {
        int64_t sum {};
        for (const auto& x : par) {
            if (x < 0) {
                sum += static_cast<int64_t>(-x) * (-x - 1);
            }
        }
        return static_cast<double>(sum) / par.size() / (par.size() - 1);
    }
};

int main() {
    using namespace std;
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    DisjointSet dsu(n);
    for (int u, v; m--;) {
        cin >> u >> v, --u, --v;
        dsu.unite(u, v);
    }
    cout << fixed << setprecision(9) << dsu.solve();
}
