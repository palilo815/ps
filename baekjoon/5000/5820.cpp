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

template <class T>
bool chmin(T& _old, T _new) { return _old > _new && (_old = _new, true); }
template <class T>
bool chmax(T& _old, T _new) { return _old < _new && (_old = _new, true); }

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    constexpr int INF = 0x3f3f3f3f;
    int n, k;
    cin >> n >> k;
    vector<vector<pair<int, int>>> adj(n);
    for (int i = n - 1, u, v, w; i--;) {
        cin >> u >> v >> w;
        adj[u].emplace_back(w, v);
        adj[v].emplace_back(w, u);
    }
    vector<int> sz(n), dist(n), best(k + 1, INF), checked;
    vector<bool> erased(n);
    vector<pair<int, int>> dists;
    int ans = INF, s;
    auto dfs_sz = y_combinator([&](auto self, int u, int p) -> int {
        sz[u] = 1;
        for (const auto& [w, v] : adj[u]) {
            if (v != p && !erased[v]) {
                sz[u] += self(v, u);
            }
        }
        return sz[u];
    });
    auto dfs_ct = y_combinator([&](auto self, int u, int p) -> int {
        for (const auto& [w, v] : adj[u]) {
            if (v != p && !erased[v] && sz[v] > s / 2) {
                return self(v, u);
            }
        }
        return u;
    });
    auto dfs = y_combinator([&](auto self, int u, int p, int edges) -> void {
        dists.emplace_back(dist[u], edges);
        checked.emplace_back(dist[u]);
        chmin(ans, edges + best[k - dist[u]]);
        for (const auto& [w, v] : adj[u]) {
            if (v != p && !erased[v] && dist[u] + w <= k) {
                dist[v] = dist[u] + w;
                self(v, u, edges + 1);
            }
        }
    });
    y_combinator([&](auto self, int u) -> void {
        s = dfs_sz(u, -1);
        u = dfs_ct(u, -1);
        erased[u] = true;
        for (const auto [w, v] : adj[u]) {
            if (erased[v] || w > k) continue;
            dist[v] = w;
            dfs(v, u, 1);
            for (const auto& [d, e] : dists) {
                chmin(best[d], e);
            }
            dists.clear();
        }
        chmin(ans, best[k]);
        for (const auto& x : checked) {
            best[x] = INF;
        }
        checked.clear();
        for (const auto& [w, v] : adj[u]) {
            if (!erased[v]) {
                self(v);
            }
        }
    })(0);
    cout << (ans == INF ? -1 : ans);
}