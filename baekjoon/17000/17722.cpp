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

struct disjoint_set {
    vector<int> par;
    disjoint_set(int n) : par(n, -1) {}
    int find(int u) {
        return par[u] < 0 ? u : par[u] = find(par[u]);
    }
    bool merge(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) return false;

        if (par[u] > par[v]) swap(u, v);
        par[u] += par[v];
        par[v] = u;
        return true;
    }
    void clear() {
        fill(par.begin(), par.end(), -1);
    }
};

template <typename node_t>
struct lazy_seg {
    lazy_seg(int _n) : n(_n), height(__lg(_n - 1) + 1), size(1 << height), tree(size << 1) {
        for (int i = 1, len = tree.size(); i < int(tree.size()); ++i) {
            if (!(i & (i - 1))) len >>= 1;
            tree[i] = len;
        }
    }

    node_t& operator[](int i) { return tree[size + i]; }
    void apply(int l, int r) {
        apply(l, r, 0, size, 1);
    }
    node_t prod(int l, int r) {
        return prod(l, r, 0, size, 1);
    }

private:
    const int n, height, size;
    vector<node_t> tree;

#define lson (i << 1)
#define rson (i << 1 | 1)
    void apply(int ql, int qr, int l, int r, int i) {
        if (qr <= l || r <= ql) return;
        if (ql <= l && r <= qr) {
            tree[i] = 0;
            return;
        }
        if (!tree[i]) push(i);

        const int m = (l + r) >> 1;
        apply(ql, qr, l, m, lson), apply(ql, qr, m, r, rson);
        pull(i);
    }
    node_t prod(int ql, int qr, int l, int r, int i) {
        if (qr <= l || r <= ql) return 0;
        if (ql <= l && r <= qr) return tree[i];
        if (!tree[i]) push(i);

        const int m = (l + r) >> 1;
        return op(prod(ql, qr, l, m, lson), prod(ql, qr, m, r, rson));
    }
    void pull(int i) {
        tree[i] = op(tree[lson], tree[rson]);
    }
    void push(int i) {
        tree[lson] = tree[rson] = 0;
    }
    node_t op(node_t lhs, node_t rhs) {
        return lhs + rhs;
    }
#undef lson
#undef rson
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, q;
    cin >> n >> q;

    disjoint_set dsu(n);
    vector<vector<int>> adj(n);

    vector<pair<int, int>> queries(q);
    for (auto& [u, v] : queries) {
        char type;
        cin >> type >> u >> v, --u, --v;
        if (type == '1') {
            if (dsu.merge(u, v))
                adj[u].emplace_back(v), adj[v].emplace_back(u);
        } else
            u = ~u, v = ~v;
    }

    // <hld>
    vector<int> par(n, -1), sz(n), top(n), in(n);
    auto dfs = y_combinator([&](auto self, int u) -> void {
        sz[u] = 1;
        for (auto& v : adj[u]) {
            par[v] = u;
            adj[v].erase(find(adj[v].begin(), adj[v].end(), u));
            self(v);
            sz[u] += sz[v];
            if (sz[v] > sz[adj[u][0]])
                swap(v, adj[u][0]);
        }
    });
    auto hld = y_combinator([&](auto self, int u) -> void {
        static int t = 0;
        in[u] = t++;
        bool heavy = true;
        for (const auto& v : adj[u]) {
            top[v] = heavy ? top[u] : v;
            self(v);
            heavy = false;
        }
    });
    // </hld>

    for (int i = 0; i < n; ++i)
        if (par[i] == -1) {
            dfs(i);
            hld(i);
        }

    lazy_seg<int> seg(n);
    auto develop = [&](int u, int v) {
        for (; top[u] != top[v]; u = par[top[u]]) {
            if (sz[top[u]] > sz[top[v]]) swap(u, v);
            seg.apply(in[top[u]], in[u] + 1);
        }
        if (in[u] > in[v]) swap(u, v);
        seg.apply(in[u] + 1, in[v] + 1);
    };
    auto counting = [&](int u, int v) {
        int res = 0;
        for (; top[u] != top[v]; u = par[top[u]]) {
            if (sz[top[u]] > sz[top[v]]) swap(u, v);
            res += seg.prod(in[top[u]], in[u] + 1);
        }
        if (in[u] > in[v]) swap(u, v);
        res += seg.prod(in[u] + 1, in[v] + 1);
        return res;
    };

    dsu.clear();

    for (const auto& [u, v] : queries)
        if (u >= 0) {
            if (!dsu.merge(u, v))
                develop(u, v);
        } else
            cout << (dsu.find(~u) == dsu.find(~v) ? counting(~u, ~v) : -1) << '\n';
}