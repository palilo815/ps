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

    vector<vector<int>> adj(n);
    for (int i = m, u, v; i--;) {
        cin >> u >> v, --u, --v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    vector<tuple<int, int, int>> ans;
    vector<bool> visited(n), is_ancestor(n);

    auto dfs = y_combinator([&](auto self, int u, int par) -> bool {
        visited[u] = is_ancestor[u] = true;
        int w = -1;
        for (const auto& v : adj[u]) {
            if (v == par) continue;
            if ((visited[v] && is_ancestor[v]) || (!visited[v] && self(v, u))) {
                if (w == -1)
                    w = v;
                else
                    ans.emplace_back(exchange(w, -1), u, v);
            }
        }
        is_ancestor[u] = false;
        if (w == -1) return true;
        if (par != -1) ans.emplace_back(par, u, w);
        return false;
    });

    for (int i = 0; i < n; ++i)
        if (!visited[i])
            dfs(i, -1);

    cout << ans.size() << '\n';
    for (const auto& [a, b, c] : ans)
        cout << a + 1 << ' ' << b + 1 << ' ' << c + 1 << '\n';
}