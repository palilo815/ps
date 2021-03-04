#include <bits/stdc++.h>
using namespace std;

struct query {
    int u, v, w, id;
};

struct BIT {
    vector<int64_t> tree;
    int n;

    BIT(int n) : tree(n + 1), n(n) {}
    void update(int i, int val) {
        for (++i; i <= n; i += i & -i)
            tree[i] += val;
    }
    int64_t query(int i) {
        int64_t ret = 0;
        for (; i; i &= i - 1)
            ret += tree[i];
        return ret;
    }
    int64_t query(int l, int r) {
        return query(r) - query(l);
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, m;
    cin >> n >> m;

    vector<int> a(n + 1);
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    a[n] = INT_MAX;

    vector<vector<int>> adj(n);
    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v, --u, --v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    vector<int> par(n), sz(n), top(n), in(n);
    int t = 0;
    function<void(int)> dfs = [&](int u) {
        sz[u] = 1;
        for (auto& v : adj[u]) {
            if (v == par[u]) continue;
            par[v] = u;
            dfs(v);
            sz[u] += sz[v];
            if (adj[u][0] == par[u] || sz[v] > sz[adj[u][0]])
                swap(v, adj[u][0]);
        }
    };
    function<void(int)> hld = [&](int u) {
        in[u] = t++;
        for (const auto& v : adj[u]) {
            if (v == par[u]) continue;
            top[v] = v == adj[u][0] ? top[u] : v;
            hld(v);
        }
    };
    dfs(0);
    hld(0);

    vector<query> q(m << 1);
    for (int i = 0, u, v, w1, w2; i < m; ++i) {
        cin >> u >> v >> w1 >> w2, --u, --v;
        q[i << 1] = {u, v, w1, ~i};
        q[i << 1 | 1] = {u, v, w2 + 1, i};
    }
    sort(q.begin(), q.end(), [&](auto& a, auto& b) {
        return a.w < b.w;
    });

    vector<int> vtx(n + 1);
    iota(vtx.begin(), vtx.end(), 0);
    sort(vtx.begin(), vtx.end(), [&](auto& x, auto& y) {
        return a[x] < a[y];
    });

    BIT bit(n);
    auto sum = [&](int u, int v) {
        int64_t res = 0;
        for (; top[u] != top[v]; u = par[top[u]]) {
            if (sz[top[u]] > sz[top[v]]) swap(u, v);
            res += bit.query(in[top[u]], in[u] + 1);
        }
        if (in[u] > in[v]) swap(u, v);
        res += bit.query(in[u], in[v] + 1);
        return res;
    };

    vector<int64_t> ans(m);
    int i = 0;
    for (const auto& [u, v, w, id] : q) {
        // a[n] is sentinel
        for (; a[vtx[i]] < w; ++i)
            bit.update(in[vtx[i]], a[vtx[i]]);
        if (id < 0)
            ans[~id] -= sum(u, v);
        else
            ans[id] += sum(u, v);
    }

    for (const auto& x : ans)
        cout << x << '\n';
}