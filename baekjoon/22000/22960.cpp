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
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n);
    for (int u, v; m--;) {
        cin >> u >> v, --u, --v;
        adj[u].emplace_back(v);
    }
    vector match(n, -1), rev(n, -1);
    vector<bool> visited(n);
    auto dfs = y_combinator([&](auto self, int u) -> bool {
        visited[u] = true;
        for (const auto& v : adj[u]) {
            if (rev[v] == -1 || (!visited[rev[v]] && self(rev[v]))) {
                return match[u] = v, rev[v] = u, true;
            }
        }
        return false;
    });
    for (bool update = true; update;) {
        fill(visited.begin(), visited.end(), false);
        update = false;
        for (int i = 0; i < n; ++i) {
            if (match[i] == -1 && dfs(i)) {
                update = true;
            }
        }
    }
    bitset<512> male;
    vector<int> stk;
    if (auto solo = find(match.begin(), match.end(), -1); solo == match.end()) {
        return cout << -1, 0;
    } else {
        stk.emplace_back(solo - match.begin());
        male._Unchecked_set(solo - match.begin());
    }
    while (!stk.empty()) {
        const auto u = stk.back();
        stk.pop_back();
        for (const auto& v : adj[u]) {
            if (~rev[v] && !male._Unchecked_test(rev[v])) {
                male._Unchecked_set(rev[v]);
                stk.emplace_back(rev[v]);
            }
        }
    }
    cout << male.count() << '\n';
    for (int i = 0; i < n; ++i) {
        if (male._Unchecked_test(i)) {
            cout << i + 1 << ' ';
        }
    }
}