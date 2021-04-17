#include <bits/stdc++.h>
using namespace std;

// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0200r0.html
namespace std {
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
struct lazy_seg {
    lazy_seg(int _n) : n(_n), height(__lg(_n - 1) + 1), size(1 << height),
                       tree(size << 1, e), lazy(size, off) {}

    node_t& operator[](int i) { return tree[size + i]; }
    void build() {
        for (int i = size - 1; i; --i)
            pull(i);
    }
    void apply(int l, int r, tag_t f) {
        apply(l, r, f, 0, size, 1);
    }
    node_t prod(int l, int r) {
        return prod(l, r, 0, size, 1);
    }

private:
    const node_t e = node_t {};
    const tag_t off = tag_t {};
    const int n, height, size;
    vector<node_t> tree;
    vector<tag_t> lazy;

    inline int get_index(node_t& node) { return &node - tree.data(); }
    inline int get_depth(node_t& node) { return __lg(get_index(node)); }
    inline int get_height(node_t& node) { return height - get_depth(node); }
    inline int get_length(node_t& node) { return 1 << get_height(node); }
    inline int get_first(node_t& node) {
        int idx = get_index(node);
        int dep = __lg(idx);
        int len = 1 << height - dep;
        return len * (idx ^ 1 << dep);
    }

#define lson (i << 1)
#define rson (i << 1 | 1)
    void apply(int ql, int qr, tag_t f, int l, int r, int i) {
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
    node_t prod(int ql, int qr, int l, int r, int i) {
        if (qr <= l || r <= ql) return e;
        if (ql <= l && r <= qr) return tree[i];
        if (lazy[i] != off) push(i);

        const auto m = (l + r) >> 1;
        return op(prod(ql, qr, l, m, lson), prod(ql, qr, m, r, rson));
    }
    void pull(int i) {
        tree[i] = op(tree[lson], tree[rson]);
    }
    void push(int i) {
        all_apply(lson, lazy[i]);
        all_apply(rson, lazy[i]);
        lazy[i] = off;
    }
    void all_apply(int i, tag_t f) {
        mapping(tree[i], f);
        if (i < size) composition(lazy[i], f);
    }
    node_t op(node_t lhs, node_t rhs) {
        return lhs + rhs;
    }
    void mapping(node_t& node, tag_t f) {
        node += int64_t(get_length(node)) * f;
    }
    void composition(tag_t& tag, tag_t f) {
        tag += f;
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

    vector<vector<int>> adj(n);
    for (int i = n - 1, u, v; i--;) {
        cin >> u >> v, --u, --v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    vector<int> in(n), out(n);
    vector<bool> visited(n);
    y_combinator([&](auto self, int u) -> void {
        static int t = 0;
        in[u] = t++;
        visited[u] = true;
        for (const auto& v : adj[u])
            if (!visited[v])
                self(v);
        out[u] = t;
    })(0);

    const auto cmp = [&](auto& a, auto& b) { return in[a] < in[b]; };
    vector<set<int, decltype(cmp)>> colour(q + 1, set<int, decltype(cmp)>(cmp));

    unordered_map<int, int> colour_idx;

    lazy_seg<int64_t, int> lazy(n);

    for (int x, c, id = 0; q--;) {
        char op;
        cin >> op >> x, --x;
        if (op == '1') {
            cin >> c, --c;
            if (!colour_idx[c]) colour_idx[c] = ++id;
            c = colour_idx[c];

            auto p = colour[c].upper_bound(x);
            if (p != colour[c].begin() && out[x] <= out[*--p])
                continue;

            for (auto it = next(colour[c].emplace_hint(p, x)); it != colour[c].end(); it = colour[c].erase(it)) {
                if (out[x] <= in[*it]) break;
                lazy.apply(in[*it], out[*it], -1);
            }
            lazy.apply(in[x], out[x], 1);
        } else
            cout << lazy.prod(in[x], out[x]) << '\n';
    }
}