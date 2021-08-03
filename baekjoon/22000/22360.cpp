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
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    string str;
    cin >> n >> str;
    vector<vector<int>> adj(n);
    for (int i = n - 1, u, v; i--;) {
        cin >> u >> v, --u, --v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    int s;
    vector<int> sz(n);
    vector<bool> erased(n);
    map<pair<int, int>, int64_t> child_map, total_map;
    auto dfs_sz = y_combinator([&](auto self, int u, int p) -> int {
        sz[u] = 1;
        for (const auto& v : adj[u]) {
            if (v != p && !erased[v]) {
                sz[u] += self(v, u);
            }
        }
        return sz[u];
    });
    auto dfs_ct = y_combinator([&](auto self, int u, int p) -> int {
        for (const auto& v : adj[u]) {
            if (v != p && !erased[v] && sz[v] > s / 2) {
                return self(v, u);
            }
        }
        return u;
    });
    auto dfs = y_combinator([&](auto self, int u, int p, pair<int, int> key) -> void {
        if (str[u] == 'U') {
            ++key.first, ++key.second;
        } else if (str[u] == 'C') {
            --key.second;
        } else {
            --key.first, ++key.second;
        }
        ++child_map[key];
        for (const auto& v : adj[u]) {
            if (v != p && !erased[v]) {
                self(v, u, key);
            }
        }
    });
    int64_t ans = 0;
    y_combinator([&](auto self, int u) -> void {
        s = dfs_sz(u, -1);
        u = dfs_ct(u, -1);
        erased[u] = true;
        total_map.clear();
        const auto key = [&](char c) -> pair<int, int> {
            if (c == 'U') return {-1, -1};
            if (c == 'C') return {0, 1};
            return {1, -1};
        }(str[u]);
        for (const auto& v : adj[u]) {
            if (erased[v]) continue;
            child_map.clear();
            dfs(v, u, pair(0, 0));
            for (const auto& [x, y] : child_map) {
                ans += y * total_map[{key.first - x.first, key.second - x.second}];
            }
            for (const auto& [x, y] : child_map) {
                total_map[x] += y;
            }
        }
        ans += total_map[key];
        for (const auto& v : adj[u]) {
            if (!erased[v]) {
                self(v);
            }
        }
    })(0);
    cout << ans;
}