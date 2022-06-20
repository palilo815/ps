#include <bits/stdc++.h>

class disjoint_set {
    std::vector<int> par;

public:
    disjoint_set(size_t n) : par(n, -1) {}

    int find(size_t u) {
        return par[u] < 0 ? u : par[u] = find(par[u]);
    }
    bool unite(size_t u, size_t v) {
        u = find(u), v = find(v);
        if (u == v) return false;
        if (par[u] > par[v]) std::swap(u, v);
        par[u] += par[v];
        par[v] = u;
        return true;
    }
};

int main() {
    using namespace std;
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    array<vector<pair<int, int>>, 11> a;
    for (int i = 0, x, y; i < n; ++i) {
        cin >> x >> y;
        a[y].emplace_back(x, i);
    }
    for (auto& xs : a) {
        sort(xs.begin(), xs.end(), [&](const auto& lhs, const auto& rhs) {
            return lhs.first < rhs.first;
        });
    }
    vector<tuple<int, int, int64_t>> edges;
    for (int y0 = 0; y0 < 11; ++y0) {
        const auto& vt = a[y0];
        for (int i = 0; i < int(vt.size()); ++i) {
            const auto& [x, id] = vt[i];
            if (i) {
                const int64_t dx = x - vt[i - 1].first;
                edges.emplace_back(vt[i - 1].second, id, dx * dx);
            }
            if (i + 1 != int(vt.size())) {
                const int64_t dx = vt[i + 1].first - x;
                edges.emplace_back(id, vt[i + 1].second, dx * dx);
            }
            for (int y1 = 0; y1 < 11; ++y1) {
                if (y0 == y1) continue;
                auto it = lower_bound(a[y1].begin(), a[y1].end(), x, [&](const auto& elem, const auto& x) {
                    return elem.first < x;
                });
                if (it != a[y1].end()) {
                    const int64_t dx = x - it->first;
                    const int64_t dy = y0 - y1;
                    edges.emplace_back(it->second, id, dx * dx + dy * dy);
                }
                if (it != a[y1].begin()) {
                    --it;
                    const int64_t dx = x - it->first;
                    const int64_t dy = y0 - y1;
                    edges.emplace_back(it->second, id, dx * dx + dy * dy);
                }
            }
        }
    }
    sort(edges.begin(), edges.end(), [&](const auto& lhs, const auto& rhs) {
        return get<2>(lhs) < get<2>(rhs);
    });
    disjoint_set dsu(n);
    int64_t ans = 0;
    for (const auto& [u, v, w] : edges) {
        if (dsu.unite(u, v)) {
            ans += w;
        }
    }
    cout << ans;
}
