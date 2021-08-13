#include <bits/stdc++.h>
using namespace std;

template <typename node_t>
class segtree {
    const node_t e = node_t {};
    const int n;
    vector<node_t> tree;

public:
    segtree(int _n) : n(_n), tree(n << 1, e) {}

    node_t& operator[](int i) { return tree[n + i]; }
    void build() {
        for (int i = n; i--;)
            pull(i);
    }
    void set(int idx, node_t val) {
        assert(0 <= idx and idx < n);
        tree[idx += n] = val;
        while (idx >>= 1) pull(idx);
    }
    node_t prod(int l, int r) {
        assert(0 <= l and l <= r and r <= n);
        node_t ret = e;
        for (l += n, r += n; l != r; l >>= 1, r >>= 1) {
            if (l & 1) ret = op(ret, tree[l++]);
            if (r & 1) ret = op(tree[--r], ret);
        }
        return ret;
    }

private:
    void pull(int i) {
        tree[i] = op(tree[i << 1], tree[i << 1 | 1]);
    }
    node_t op(node_t lhs, node_t rhs) {
        return max(lhs, rhs);
    }
};

template <typename T, typename f = less<T>>
class disjoint_set {
    // change this (1/1)
    const T e = 0x3f3f3f3f;
    const f cmp {};
    // change this (1/1)
    const int n;
    vector<int> par;
    vector<T> weight;

public:
    disjoint_set(int n) : n(n), par(n, -1), weight(n, e) {}
    int find(int u) {
        while (par[u] >= 0) u = par[u];
        return u;
    }
    void unite(int u, int v, T w) {
        u = find(u), v = find(v);
        if (u == v) return;
        if (par[u] > par[v]) swap(u, v);
        par[u] += par[v];
        par[v] = u;
        weight[v] = w;
    }
    T query(int u, int v) {
        T ret = e;
        for (; u != v; u = par[u]) {
            if (cmp(weight[v], weight[u])) swap(u, v);
            ret = weight[u];
        }
        return ret;
    }
};

struct edge_t {
    int u, v, w;
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, q;
    cin >> n >> q;
    vector<edge_t> edge(n - 1);
    for (auto& [u, v, w] : edge) {
        cin >> u >> v >> w, --u, --v;
    }
    sort(edge.begin(), edge.end(), [&](const auto& lhs, const auto& rhs) {
        return lhs.w < rhs.w;
    });
    disjoint_set<int> dsu(n);
    for (const auto& [u, v, w] : edge) {
        dsu.unite(u, v, w);
    }
    segtree<int> seg(n - 1);
    for (int i = 0; i < n - 1; ++i) {
        seg[i] = dsu.query(i, i + 1);
    }
    seg.build();
    for (int l, r; q--;) {
        cin >> l >> r, --l, --r;
        cout << seg.prod(l, r) << '\n';
    }
}