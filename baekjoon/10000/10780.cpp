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
    cin >> n;
    vector<vector<int>> adj(n);
    for (int u, v, i = n - 1; i--;) {
        cin >> u >> v, --u, --v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    const int root = find_if(adj.begin(), adj.end(), [&](const auto& x) {
        return x.size() != 1;
    }) - adj.begin();
    vector<int> leaves;
    leaves.reserve(n - 1);
    y_combinator([&](auto self, int u) -> void {
        if (adj[u].empty()) {
            leaves.emplace_back(u);
        } else {
            for (const auto& v : adj[u]) {
                adj[v].erase(find(adj[v].begin(), adj[v].end(), u));
                self(v);
            }
        }
    })(root);
    cout << (leaves.size() + 1) / 2 << '\n';
    for (int i = 0; i < int(leaves.size() + 1) / 2; ++i) {
        cout << leaves[i] + 1 << ' ' << leaves[i + leaves.size() / 2] + 1 << '\n';
    }
}