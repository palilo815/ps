#include <bits/stdc++.h>
using namespace std;

template <typename node_t, typename tag_t>
class lazy_segtree {
    // change this (1/2)
    const node_t e {};
    const tag_t off {};
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
        assert(0 <= l and l <= r and r <= n);
        apply(l, r, f, 0, size, 1);
    }
    node_t prod(size_t l, size_t r) {
        assert(0 <= l and l <= r and r <= n);
        return prod(l, r, 0, size, 1);
    }
    node_t all_prod() const {
        return tree[1];
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
    node_t op(node_t lhs, node_t rhs) const {
        return max(lhs, rhs);
    }
    void mapping(node_t& node, tag_t f) {
        node += f;
    }
    void composition(tag_t& tag, tag_t f) {
        tag += f;
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
    constexpr int INF = 0x3f3f3f3f;
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    vector<pair<int, int>> query(q);
    for (auto& [v, i] : query) {
        cin >> i >> v;
    }
    vector<pair<int, int>> vals(n + q);
    for (int i = 0; i < n; ++i) {
        vals[i] = {a[i], i};
    }
    copy(query.begin(), query.end(), vals.begin() + n);
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    auto get_index = [&](const pair<int, int>&& x) {
        return lower_bound(vals.begin(), vals.end(), x) - vals.begin();
    };
    const size_t m = vals.size();
    lazy_segtree<int, int> lazy(m);
    lazy.apply(0, m, -INF);
    for (int i = 0; i < n; ++i) {
        auto id = get_index(pair(a[i], i));
        lazy.apply(id, id + 1, INF + i);
        lazy.apply(id + 1, m, -1);
    }
    for (const auto& [v, i] : query) {
        auto id = get_index(pair(a[i], i));
        lazy.apply(id, id + 1, -(INF + i));
        lazy.apply(id + 1, m, 1);
        a[i] = v;
        id = get_index(pair(a[i], i));
        lazy.apply(id, id + 1, INF + i);
        lazy.apply(id + 1, m, -1);
        cout << lazy.all_prod() << '\n';
    }
}