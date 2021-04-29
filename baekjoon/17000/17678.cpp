#include <bits/stdc++.h>
using namespace std;

namespace std {
// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0200r0.html
template <class Fun>
class y_combinator_result {
    Fun fun_;

public:
    template <class T>
    explicit y_combinator_result(T&& fun) : fun_(std::forward<T>(fun)) {}

    template <class... Args>
    decltype(auto) operator()(Args&&... args) {
        return fun_(std::ref(*this), std::forward<Args>(args)...);
    }
};

template <class Fun>
decltype(auto) y_combinator(Fun&& fun) {
    return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
}
}; // namespace std

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, k;
    cin >> n >> k;

    vector<vector<int>> adj(n);
    for (int i = n - 1, u, v; i--;) {
        cin >> u >> v, --u, --v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    vector<vector<int>> colour(k);
    for (int i = 0, c; i < n; ++i) {
        cin >> c, --c;
        colour[c].emplace_back(i);
    }

    vector<int> par(n), dep(n);
    par[0] = -1;
    y_combinator([&](auto self, int u) -> void {
        for (const auto& v : adj[u]) {
            if (v == par[u]) continue;
            par[v] = u, dep[v] = dep[u] + 1;
            self(v);
        }
    })(0);

    vector dsu(n, -1);
    auto get_par = [&](int u) {
        while (dsu[u] != -1) {
            if (dsu[dsu[u]] != -1) dsu[u] = dsu[dsu[u]];
            u = dsu[u];
        }
        return u;
    };

    for (const auto& nodes : colour) {
        int u = get_par(nodes[0]), p;
        for (auto v : nodes) {
            for (v = get_par(v); u != v; u = p) {
                if (dep[u] < dep[v]) swap(u, v);
                p = get_par(par[u]);
                dsu[u] = p;
            }
        }
    }

    vector<int> deg(n);
    for (int u = 0; u < n; ++u) {
        int pu = get_par(u);
        for (const auto& v : adj[u]) {
            if (v == par[u]) continue;
            if (int pv = get_par(v); pu != pv)
                ++deg[pu], ++deg[pv];
        }
    }
    cout << ((count(deg.begin(), deg.end(), 1) + 1) >> 1);
}