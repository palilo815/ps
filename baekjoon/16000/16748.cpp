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
    int n;
    cin >> n;

    vector<vector<int>> adj(n);
    for (int i = n - 1, u, v; i--;) {
        cin >> u >> v, --u, --v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    vector<int> colour(n);
    for (auto& x : colour) cin >> x, --x;

    // <hld>
    vector<int> par(n), sz(n), top(n), in(n), dep(n);
    y_combinator([&](auto self, int u) -> void {
        sz[u] = 1;
        for (auto& v : adj[u]) {
            par[v] = u, dep[v] = dep[u] + 1;
            adj[v].erase(find(adj[v].begin(), adj[v].end(), u));
            self(v);
            sz[u] += sz[v];
            if (sz[v] > sz[adj[u][0]])
                swap(v, adj[u][0]);
        }
    })(0);
    y_combinator([&](auto self, int u) -> void {
        static int t = 0;
        in[u] = t++;
        bool heavy = true;
        for (const auto& v : adj[u]) {
            top[v] = heavy ? top[u] : v;
            self(v);
            heavy = false;
        }
    })(0);
    // </hld>

    auto lca = [&](int u, int v) {
        for (; top[u] != top[v]; u = par[top[u]])
            if (sz[top[u]] > sz[top[v]])
                swap(u, v);
        return in[u] < in[v] ? u : v;
    };

    constexpr int mxC = 1e5;

    auto cmp = [&](auto& a, auto& b) { return in[a] < in[b]; };
    vector<set<int, decltype(cmp)>> nodes(mxC, set<int, decltype(cmp)>(cmp));

    array<int, mxC> ans {};
    auto add = [&](int c, int u) {
        ans[c] += dep[u];
        auto it = nodes[c].emplace(u).first;
        if (int(nodes[c].size()) == 1) return;

        auto a = it == nodes[c].begin() ? *nodes[c].rbegin() : *prev(it);
        auto b = ++it == nodes[c].end() ? *nodes[c].begin() : *it;
        if (a != b) ans[c] += dep[lca(a, b)];
        ans[c] -= dep[lca(a, u)] + dep[lca(b, u)];
    };
    auto rem = [&](int c, int u) {
        ans[c] -= dep[u];
        auto it = nodes[c].erase(nodes[c].find(u));
        if (nodes[c].empty()) return;

        auto a = it == nodes[c].begin() ? *nodes[c].rbegin() : *prev(it);
        auto b = it == nodes[c].end() ? *nodes[c].begin() : *it;
        if (a != b) ans[c] -= dep[lca(a, b)];
        ans[c] += dep[lca(a, u)] + dep[lca(b, u)];
    };

    for (int i = 0; i < n; ++i)
        add(colour[i], i);

    int q;
    cin >> q;

    for (int x, y; q--;) {
        char op;
        cin >> op >> x, --x;
        if (op == 'U') {
            cin >> y, --y;
            rem(exchange(colour[x], y), x);
            add(colour[x], x);
        } else
            cout << (nodes[x].size() > 1 ? ans[x] : 0 - nodes[x].empty()) << '\n';
    }
}