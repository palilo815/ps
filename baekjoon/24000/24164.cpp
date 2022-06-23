#include <bits/stdc++.h>

class DisjointSet {
    std::vector<int> par;

public:
    DisjointSet() = default;
    explicit DisjointSet(size_t n) : par(n, -1) {}

    auto find(int u) -> int {
        return par[u] < 0 ? u : par[u] = find(par[u]);
    }

    auto unite(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) return false;
        if (par[u] > par[v]) std::swap(u, v);
        par[u] += par[v];
        par[v] = u;
        return true;
    }

    auto size_of(int u) { return -par[find(u)]; }

    auto same(int u, int v) { return find(u) == find(v); }

    [[nodiscard]] auto num_components() const {
        return std::count_if(par.begin(), par.end(), [&](const auto& x) { return x < 0; });
    }
};

auto main() -> int {
    using namespace std;
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    DisjointSet dsu(n);
    for (int u, v; m--;) {
        cin >> u >> v, --u, --v;
        dsu.unite(u, v);
    }
    cout << dsu.num_components() - 1;
}
