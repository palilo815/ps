#include <bits/stdc++.h>

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
    using namespace std;
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, m, s;
    cin >> n >> m >> s, --s;
    vector<vector<int>> adj(n);
    for (int u, v; m--;) {
        cin >> u >> v, --u, --v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    ranges::for_each(adj, [&](auto& x) { ranges::sort(x); });
    vector dep(n, -1);
    dep[s] = 0;
    y_combinator([&](auto self, int u) -> void {
        for (const auto& v : adj[u] | views::filter([&](const auto& v) { return dep[v] == -1; })) {
            dep[v] = dep[u] + 1;
            self(v);
        }
    })(s);
    for (const auto& x : dep) {
        cout << x << '\n';
    }
}
