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

    void answer() {
        cout << count_if(par.begin(), par.end(), [&](const auto& x) { return x < 0; })
             << ' '
             << -*min_element(par.begin(), par.end());
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    int n, d;
    cin >> n >> d;

    vector<pair<int, int>> a(n);
    for (auto& [x, y] : a) cin >> x >> y;

    vector<int> id(n);
    iota(id.begin(), id.end(), 0);

    vector<pair<int, int>> edges;
    edges.reserve(n << 2);

    for (int t = 0; t < 4; ++t) {
        sort(id.begin(), id.end(), [&](auto& lhs, auto& rhs) {
            return a[lhs].first - a[rhs].first < a[rhs].second - a[lhs].second;
        });

        map<int, int, greater<int>> sweep;
        for (const auto& i : id) {
            for (auto it = sweep.lower_bound(a[i].second); it != sweep.end(); it = sweep.erase(it)) {
                int j = it->second;
                int dx = a[i].first - a[j].first, dy = a[i].second - a[j].second;
                if (dy > dx) break;
                if (dx + dy <= d) edges.emplace_back(i, j);
            }
            sweep[a[i].second] = i;
        }

        for (auto& [x, y] : a)
            if (t & 1)
                x = -x;
            else
                swap(x, y);
    }

    disjoint_set dsu(n);
    for (const auto& [u, v] : edges)
        dsu.unite(u, v);
    dsu.answer();
}