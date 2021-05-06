#include <bits/stdc++.h>
using namespace std;

template <class T>
bool chmin(T& _old, T _new) { return _old > _new && (_old = _new, true); }
template <class T>
bool chmax(T& _old, T _new) { return _old < _new && (_old = _new, true); }

class disjoint_set {
public:
    vector<int> par, max_id;
    vector<bool> has_cycle;

    disjoint_set(int n) : par(n, -1), max_id(n), has_cycle(n) {
        iota(max_id.begin(), max_id.end(), 0);
    }
    int find(int u) {
        return par[u] < 0 ? u : par[u] = find(par[u]);
    }
    void merge(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) {
            has_cycle[u] = true;
            return;
        }

        if (par[u] > par[v]) swap(u, v);
        par[u] += par[v];
        par[v] = u;

        chmax(max_id[u], max_id[v]);
        has_cycle[u] = has_cycle[u] | has_cycle[v];
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n;

    vector<pair<int, int>> a(n);
    for (auto& [x, y] : a) cin >> x >> y;

    vector<int> ord(n << 1);
    memmove(ord.data(), a.data(), sizeof(int) * n * 2);
    sort(ord.begin(), ord.end());
    ord.erase(unique(ord.begin(), ord.end()), ord.end());

    int m = ord.size();

    for (auto& [x, y] : a)
        x = lower_bound(ord.begin(), ord.end(), x) - ord.begin(),
        y = lower_bound(ord.begin(), ord.end(), y) - ord.begin();

    vector out_degree(m, -1);

    disjoint_set dsu(m);
    for (const auto& [x, y] : a) {
        ++out_degree[x], ++out_degree[y];
        dsu.merge(x, y);
    }

    int64_t ans = 0;
    for (int i = 0; i < m; ++i) {
        ans += int64_t(out_degree[i]) * ord[i];
        if (dsu.par[i] < 0 && !dsu.has_cycle[i])
            ans += ord[dsu.max_id[i]];
    }
    cout << ans;
}