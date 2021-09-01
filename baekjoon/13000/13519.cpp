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

template <typename node_t, typename tag_t>
class lazy_segtree {
    // change this (1/2)
    const node_t e {};
    const tag_t off = 0x3f3f3f3f;
    // change this (1/2)
    const size_t n, height, size;
    vector<node_t> tree;
    vector<tag_t> lazy;

public:
    lazy_segtree(size_t n) : n(n), height(n ? __lg(n - 1) + 1 : 0), size(1 << height),
                             tree(size << 1, e), lazy(size, off) {}

    node_t& operator[](size_t i) { return tree[size + i]; }
    void build() {
        for (size_t i = size; i--;) {
            pull(i);
        }
    }
    void apply(size_t l, size_t r, tag_t f) {
        apply(l, r, f, 0, size, 1);
    }
    node_t prod(size_t l, size_t r) {
        return prod(l, r, 0, size, 1);
    }
    node_t all_prod() const {
        return tree[1];
    }
    node_t op(node_t lhs, node_t rhs) const {
        return node_t {
            max(lhs.lmax, lhs.sum + rhs.lmax),
            max({lhs.cmax, rhs.cmax, lhs.rmax + rhs.lmax}),
            max(rhs.rmax, rhs.sum + lhs.rmax),
            lhs.sum + rhs.sum};
    }

private:
#define lson (i << 1)
#define rson (i << 1 | 1)
    inline int get_index(node_t& node) const { return &node - tree.data(); }
    inline int get_depth(node_t& node) const { return __lg(get_index(node)); }
    inline int get_height(node_t& node) const { return height - get_depth(node); }
    inline int get_length(node_t& node) const { return 1 << get_height(node); }
    inline int get_first(node_t& node) const {
        int idx = get_index(node);
        int dep = __lg(idx);
        int len = 1 << height - dep;
        return len * (idx ^ 1 << dep);
    }
    void apply(size_t ql, size_t qr, tag_t f, size_t l, size_t r, size_t i) {
        if (qr <= l || r <= ql) return;
        if (ql <= l && r <= qr) {
            all_apply(i, f);
            return;
        }
        if (lazy[i] != off) push(i);

        const auto m = (l + r) >> 1;
        apply(ql, qr, f, l, m, lson), apply(ql, qr, f, m, r, rson);
        pull(i);
    }
    node_t prod(size_t ql, size_t qr, size_t l, size_t r, size_t i) {
        if (qr <= l || r <= ql) return e;
        if (ql <= l && r <= qr) return tree[i];
        if (lazy[i] != off) push(i);

        const auto m = (l + r) >> 1;
        return op(prod(ql, qr, l, m, lson), prod(ql, qr, m, r, rson));
    }
    void pull(size_t i) {
        tree[i] = op(tree[lson], tree[rson]);
    }
    void push(size_t i) {
        all_apply(lson, lazy[i]);
        all_apply(rson, lazy[i]);
        lazy[i] = off;
    }
    void all_apply(size_t i, tag_t f) {
        mapping(tree[i], f);
        if (i < size) composition(lazy[i], f);
    }
    // change this (2/2)
    void mapping(node_t& node, tag_t f) {
        const auto sum = f * get_length(node);
        node = f > 0 ? node_t {sum, sum, sum, sum} : node_t {0, 0, 0, sum};
    }
    void composition(tag_t& tag, tag_t f) {
        tag = f;
    }
    // change this (2/2)
#undef lson
#undef rson
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& x : a) {
        cin >> x;
    }
    vector<vector<int>> adj(n);
    for (int i = n - 1, u, v; i--;) {
        cin >> u >> v, --u, --v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    vector<int> par(n), sz(n), top(n), in(n);
    par[0] = -1;
    int tick = 0;
    y_combinator([&](auto self, int u) -> void {
        sz[u] = 1;
        for (auto& v : adj[u]) {
            par[v] = u;
            adj[v].erase(find(adj[v].begin(), adj[v].end(), u));
            self(v);
            sz[u] += sz[v];
            if (sz[v] > sz[adj[u][0]]) swap(v, adj[u][0]);
        }
    })(0);
    y_combinator([&](auto self, int u) -> void {
        in[u] = tick++;
        bool heavy = true;
        for (const auto& v : adj[u]) {
            top[v] = heavy ? top[u] : v;
            self(v);
            heavy = false;
        }
    })(0);
    struct node_t {
        int lmax, cmax, rmax, sum;
    };
    lazy_segtree<node_t, int> lazy(n);
    for (int i = 0; i < n; ++i) {
        lazy[in[i]].sum = a[i];
        if (a[i] > 0) {
            lazy[in[i]].lmax = lazy[in[i]].cmax = lazy[in[i]].rmax = a[i];
        }
    }
    lazy.build();
    auto path_update = [&](int u, int v, int w) {
        for (; top[u] != top[v]; u = par[top[u]]) {
            if (sz[top[u]] > sz[top[v]]) swap(u, v);
            lazy.apply(in[top[u]], in[u] + 1, w);
        }
        if (in[u] > in[v]) swap(u, v);
        lazy.apply(in[u], in[v] + 1, w);
    };
    auto path_query = [&](int u, int v) {
        node_t res_u {}, res_v {};
        while (top[u] != top[v]) {
            if (sz[top[u]] < sz[top[v]]) {
                res_u = lazy.op(lazy.prod(in[top[u]], in[u] + 1), res_u);
                u = par[top[u]];
            } else {
                res_v = lazy.op(lazy.prod(in[top[v]], in[v] + 1), res_v);
                v = par[top[v]];
            }
        }
        if (in[u] > in[v]) swap(u, v), swap(res_u, res_v);
        res_v = lazy.op(lazy.prod(in[u], in[v] + 1), res_v);
        return max({res_u.cmax, res_v.cmax, res_u.lmax + res_v.lmax});
    };
    int q;
    cin >> q;
    for (int u, v, w; q--;) {
        char op;
        cin >> op >> u >> v, --u, --v;
        if (op == '1') {
            cout << path_query(u, v) << '\n';
        } else {
            cin >> w;
            path_update(u, v, w);
        }
    }
}