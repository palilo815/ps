#include <bits/stdc++.h>

class DisjointSet {
    std::vector<int> par;

public:
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
};

auto main() -> int {
    using namespace std;
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<tuple<int, int, int>> edges(n - 1);
    for (auto& [u, v, w] : edges) {
        cin >> u >> v >> w, --u, --v;
    }
    sort(edges.begin(), edges.end(), [&](const auto& lhs, const auto& rhs) {
        return get<2>(lhs) > get<2>(rhs);
    });
    DisjointSet dsu(n);
    int64_t ans = 0;
    for (const auto& [u, v, w] : edges) {
        dsu.unite(u, v);
        ans = max(ans, static_cast<int64_t>(w) * (dsu.size_of(u) - 1));
    }
    cout << ans;
}
