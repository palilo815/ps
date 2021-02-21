#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 1000000007;

template <typename node_t, typename tag_t>
struct lazy_segtree {
    lazy_segtree(int _n) : n(_n), height(32 - __builtin_clz(_n - 1)), size(1 << height) {
        tree.resize(size << 1, e);
        lazy.resize(size, off);
    }

#define lson (i << 1)
#define rson (i << 1 | 1)
    node_t& operator[](int i) { return tree[size + i]; }
    void build() {
        for (int i = size - 1; i; --i)
            pull(i);
    }
    void set(int idx, node_t val) {
        assert(0 <= idx and idx < n);
        idx += size;

        for (int i = height; i; --i)
            push(idx >> i);

        tree[idx] = val;
        while (idx >>= 1) pull(idx);
    }
    node_t get(int idx) {
        assert(0 <= idx and idx < n);
        idx += size;

        for (int i = height; i; --i)
            push(idx >> i);

        return tree[idx];
    }
    node_t prod(int l, int r) {
        assert(0 <= l and l <= r and r <= n);
        l += size, r += size;

        for (int i = height; i; --i) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }

        node_t lval = e, rval = e;
        for (; l != r; l >>= 1, r >>= 1) {
            if (l & 1) lval = op(lval, tree[l++]);
            if (r & 1) rval = op(tree[--r], rval);
        }
        return op(lval, rval);
    }
    void apply(int idx, tag_t f) {
        assert(0 <= idx and idx < n);
        idx += size;

        for (int i = height; i; --i)
            push(idx >> i);

        mapping(tree[idx], f);
        while (idx >>= 1) pull(idx);
    }
    void apply(int l, int r, tag_t f) {
        assert(0 <= l and l <= r and r <= n);
        if (l == r) return;
        l += size, r += size;

        for (int i = height; i; --i) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }

        const int l0 = l, r0 = r;
        for (; l != r; l >>= 1, r >>= 1) {
            if (l & 1) all_apply(l++, f);
            if (r & 1) all_apply(--r, f);
        }
        l = l0, r = r0;

        for (int i = 1; i <= height; ++i) {
            if (((l >> i) << i) != l) pull(l >> i);
            if (((r >> i) << i) != r) pull((r - 1) >> i);
        }
    }

private:
    const int n, height, size;
    vector<node_t> tree;
    vector<tag_t> lazy;
    const node_t e = node_t {};
    const tag_t off = tag_t {};

    inline int get_index(node_t& node) { return &node - tree.data(); }
    inline int get_depth(node_t& node) { return 31 - __builtin_clz(get_index(node)); }
    inline int get_height(node_t& node) { return height - get_depth(node); }
    inline int get_length(node_t& node) { return 1 << get_height(node); }
    inline int get_lo(node_t& node) {
        int idx = get_index(node);
        int dep = 31 - __builtin_clz(idx);
        int len = 1 << height - dep;
        return len * (idx ^ 1 << dep);
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
    void mul(int a[][2], int b[][2], int c[][2]) {
        c[0][0] = (int64_t(a[0][0]) * b[0][0] + int64_t(a[0][1]) * b[1][0]) % mod;
        c[0][1] = (int64_t(a[0][0]) * b[0][1] + int64_t(a[0][1]) * b[1][1]) % mod;
        c[1][0] = (int64_t(a[1][0]) * b[0][0] + int64_t(a[1][1]) * b[1][0]) % mod;
        c[1][1] = (int64_t(a[1][0]) * b[0][1] + int64_t(a[1][1]) * b[1][1]) % mod;
    }
    node_t op(node_t lhs, node_t rhs) {
        node_t ret;
        mul(rhs.ori, lhs.ori, ret.ori);
        mul(rhs.rev, lhs.rev, ret.rev);
        return ret;
    }
    void mapping(node_t& node, tag_t f) {
        if (f) swap(node.ori, node.rev);
    }
    void composition(tag_t& tag, tag_t f) {
        tag ^= f;
    }
#undef lson
#undef rson
};

#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, q;
    cin >> n >> q;

    struct node_t {
        int ori[2][2] = {1, 0, 0, 1}, rev[2][2] = {1, 0, 0, 1};
    };

    lazy_segtree<node_t, char> seg(n);
    for (int i = 0; i < n; ++i) {
        char c;
        cin >> c;
        if (c == 'A')
            seg[i].ori[0][1] = 1, seg[i].rev[1][0] = 1;
        else
            seg[i].ori[1][0] = 1, seg[i].rev[0][1] = 1;
    }
    seg.build();

    char op;
    int64_t a, b;
    for (int l, r; q--;) {
        cin >> op >> l >> r, --l;
        if (op == '1') seg.apply(l, r, true);
        else {
            cin >> a >> b;
            auto res = seg.prod(l, r);
            cout << (res.ori[0][0] * a + res.ori[0][1] * b) % mod << ' '
                 << (res.ori[1][0] * a + res.ori[1][1] * b) % mod << '\n';
        }
    }
}