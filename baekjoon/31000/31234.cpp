#include <bits/stdc++.h>

class LazySeg {
    const int size;
    std::vector<int64_t> tree, lazy;

public:
    explicit LazySeg(int n) : size(1 << (std::__lg(n - 1) + 1)), tree(size << 1, INT_MAX), lazy(size) {}

    auto operator[](int i) -> int64_t& { return tree[i + size]; }

    auto build() -> void {
        for (auto i = size; --i;) {
            tree[i] = std::min(tree[i << 1], tree[i << 1 | 1]);
        }
    }

    auto apply(int l, int r, int64_t v) -> void {
        apply(l, r, v, 0, size, 1);
    }

    [[nodiscard]] auto all_prod() const -> int64_t {
        return tree[1];
    }

private:
    auto apply(int ql, int qr, int64_t v, int l, int r, int i) -> void {
        if (qr <= l || r <= ql) return;
        if (ql <= l && r <= qr) {
            all_apply(i, v);
            return;
        }
        if (lazy[i]) push(i);
        auto const m = (l + r) >> 1;
        apply(ql, qr, v, l, m, i << 1);
        apply(ql, qr, v, m, r, i << 1 | 1);
        tree[i] = std::min(tree[i << 1], tree[i << 1 | 1]);
    }

    auto all_apply(int i, int64_t v) -> void {
        tree[i] += v;
        if (i < size) lazy[i] += v;
    }

    auto push(int i) -> void {
        all_apply(i << 1, lazy[i]);
        all_apply(i << 1 | 1, lazy[i]);
        lazy[i] = 0;
    }
};

auto main() -> int {
    using namespace std;
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n);
    for (int i = n, u, v; --i;) {
        cin >> u >> v, --u, --v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    vector<int> topo(1), par(n, -1);
    topo.reserve(n);
    for (auto i = 0; i < n; ++i) {
        auto const u = topo[i];
        for (auto const& v : adj[u]) {
            par[v] = u;
            auto const it = find(adj[v].begin(), adj[v].end(), u);
            swap(*it, adj[v].back());
            adj[v].pop_back();
            topo.emplace_back(v);
        }
    }
    vector sz(n, 1);
    for (auto i = n; --i;) {
        auto const u = topo[i];
        sz[par[u]] += sz[u];
    }
    vector<int> top(n);
    for (auto i = 0; i < n; ++i) {
        auto const u = topo[i];
        auto const heavy = max_element(adj[u].begin(), adj[u].end(), [&](auto l, auto r) { return sz[l] < sz[r]; });
        iter_swap(adj[u].begin(), heavy);
        auto acc = 1;
        for (auto const& v : adj[u]) {
            top[v] = v == adj[u][0] ? top[u] : v;
            topo[i + acc] = v;
            acc += sz[v];
        }
    }
    vector<int> tin(n);
    for (auto i = 0; i < n; ++i) {
        tin[topo[i]] = i;
    }
    vector<int> a(n);
    for (auto& x : a) {
        cin >> x;
    }
    LazySeg lazy(n);
    for (auto i = 0; i < n; ++i) {
        lazy[i] = a[topo[i]];
    }
    lazy.build();
    for (int i = 0, u, v, w; i < m; ++i) {
        cin >> u >> v >> w, --u, --v;
        for (; top[u] != top[v]; u = par[top[u]]) {
            if (sz[top[u]] > sz[top[v]]) swap(u, v);
            lazy.apply(tin[top[u]], tin[u] + 1, -w);
        }
        if (tin[u] > tin[v]) swap(u, v);
        lazy.apply(tin[u], tin[v] + 1, -w);
        if (lazy.all_prod() < 0) return cout << i, 0;
    }
    cout << m;
}
