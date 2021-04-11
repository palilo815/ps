#include <bits/stdc++.h>
using namespace std;

constexpr int INF = 0x3f3f3f3f;

struct elem {
    int d, u;
    elem(int d, int u) : d(d), u(u) {}
    bool operator<(const elem& rhs) const {
        return d > rhs.d;
    }
};

template <typename node_t>
struct lazy_seg {
    lazy_seg(int _n) : n(_n), height(__lg(_n - 1) + 1), size(1 << height),
                       tree(size << 1, e) {}

    node_t& operator[](int i) { return tree[size + i]; }
    void build() {
        for (int i = size - 1; i; --i)
            pull(i);
    }
    void push_down() {
        for (int i = 1; i < size; ++i)
            push(i);
    }
    void apply(int l, int r, node_t f) {
        assert(l < r);
        apply(l, r, f, 0, size, 1);
    }

private:
    const node_t e = INF;
    const int n, height, size;
    vector<node_t> tree;

#define lson (i << 1)
#define rson (i << 1 | 1)
    void apply(int ql, int qr, node_t qv, int l, int r, int i) {
        if (qr <= l || r <= ql) return;
        if (ql <= l && r <= qr) {
            tree[i] = min(tree[i], qv);
            return;
        }
        push(i);

        const auto m = (l + r) >> 1;
        apply(ql, qr, qv, l, m, lson), apply(ql, qr, qv, m, r, rson);
        pull(i);
    }
    void pull(int i) {
        tree[i] = max(tree[lson], tree[rson]);
    }
    void push(int i) {
        tree[lson] = min(tree[lson], tree[i]);
        tree[rson] = min(tree[rson], tree[i]);
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
    int n, m, src, dst;
    cin >> n >> m >> src >> dst, --src, --dst;

    vector<vector<pair<int, int>>> adj(n);
    for (int u, v, w; m--;) {
        cin >> u >> v >> w, --u, --v;
        adj[u].emplace_back(w, v);
        adj[v].emplace_back(w, u);
    }

    int k;
    cin >> k;

    vector<int> lucky(k);
    for (auto& x : lucky) cin >> x, --x;

    vector<int> order(n, -1);
    for (int i = 0; i < k; ++i)
        order[lucky[i]] = i;

    vector<int> d1(n, INF), d2(n, INF), par(n, -1);
    auto dijk = [&](int s, vector<int>& dist) {
        priority_queue<elem> pq;
        pq.emplace(dist[s] = 0, s);

        while (!pq.empty()) {
            const auto [d, u] = pq.top();
            pq.pop();
            if (d != dist[u]) continue;

            for (const auto& [w, v] : adj[u])
                if (dist[v] > d + w) {
                    pq.emplace(dist[v] = d + w, v);
                    par[v] = u;
                }
        }
    };
    dijk(dst, d2);
    dijk(src, d1);

    par[src] = -1;
    for (int i = 1; i < k; ++i)
        par[lucky[i]] = lucky[i - 1];

    vector<int> idx(n);
    iota(idx.begin(), idx.end(), 0);
    sort(idx.begin(), idx.end(), [&](auto& a, auto& b) {
        return d1[a] < d1[b];
    });

    lucky.resize(n);
    for (const auto& u : idx)
        lucky[u] = order[u] == -1 ? lucky[par[u]] : order[u];

    lazy_seg<int> seg(k - 1);
    for (int u = 0, l, r, d; u < n; ++u)
        for (const auto& [w, v] : adj[u]) {
            if (u > v || (~order[u] && ~order[v] && abs(order[u] - order[v]) == 1) || lucky[u] == lucky[v])
                continue;
            if (lucky[u] < lucky[v]) {
                l = lucky[u], r = lucky[v];
                d = d1[u] + d2[v] + w;
            } else {
                l = lucky[v], r = lucky[u];
                d = d2[u] + d1[v] + w;
            }
            seg.apply(l, r, d);
        }

    seg.push_down();
    for (int i = 0; i < k - 1; ++i)
        cout << (seg[i] == INF ? -1 : seg[i]) << '\n';
}