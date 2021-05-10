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
    int n, m;
    cin >> n >> m;

    if (m & 1) return cout << "impossible", 0;

    vector<vector<pair<int, int>>> adj(n); // {who, v}
    for (int i = 0, u, v; i < m; ++i) {
        cin >> u >> v;
        adj[u].emplace_back(i, v);
        adj[v].emplace_back(i, u);
    }

    vector<pair<int, int>> ans;
    vector<bool> visited(n), is_ancestor(n);

    auto dfs = y_combinator([&](auto self, int u, int par_id) -> bool {
        visited[u] = is_ancestor[u] = true;
        int id_0 = -1;
        for (const auto& [id_1, v] : adj[u]) {
            if (id_1 == par_id) continue;
            if ((visited[v] && is_ancestor[v]) || (!visited[v] && self(v, id_1)))
                if (id_0 == -1)
                    id_0 = id_1;
                else
                    ans.emplace_back(exchange(id_0, -1), id_1);
        }
        is_ancestor[u] = false;
        if (id_0 == -1) return true;
        if (par_id != -1) ans.emplace_back(par_id, id_0);
        return false;
    });

    for (int i = 0; i < n; ++i)
        if (!visited[i])
            dfs(i, -1);

    if (int(ans.size()) != (m >> 1)) return cout << "impossible", 0;

    for (const auto& [u, v] : ans)
        cout << u << ' ' << v << '\n';
}