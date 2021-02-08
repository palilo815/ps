#include <bits/stdc++.h>
using namespace std;

struct query {
    int l, r, lca, id;
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n;

    vector<int> a(n);
    for (auto& x : a) cin >> x;

    vector<int> vt = a;
    sort(vt.begin(), vt.end());
    vt.erase(unique(vt.begin(), vt.end()), vt.end());
    for (auto& x : a)
        x = lower_bound(vt.begin(), vt.end(), x) - vt.begin();

    vector<vector<int>> adj(n);
    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v, --u, --v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    int t = 0;
    vector<int> in(n), out(n), tour(n << 1), sz(n), par(n), top(n);
    function<void(int)> dfs = [&](int u) {
        sz[u] = 1;
        for (auto& v : adj[u]) {
            if (v == par[u]) continue;
            par[v] = u;
            dfs(v);
            sz[u] += sz[v];
            if (adj[u][0] == par[u] || sz[v] > sz[adj[u][0]])
                swap(v, adj[u][0]);
        };
    };
    function<void(int)> hld = [&](int u) {
        in[u] = t, tour[t] = u;
        ++t;
        for (const auto v : adj[u]) {
            if (v == par[u]) continue;
            top[v] = v == adj[u][0] ? top[u] : v;
            hld(v);
        }
        out[u] = t, tour[t] = u;
        ++t;
    };
    dfs(0);
    hld(0);

    auto lca = [&](int u, int v) {
        for (; top[u] != top[v]; u = par[top[u]])
            if (sz[top[u]] > sz[top[v]])
                swap(u, v);
        return in[u] < in[v] ? u : v;
    };

    int m;
    cin >> m;

    vector<query> q(m);
    for (int i = 0, u, v; i < m; ++i) {
        cin >> u >> v, --u, --v;
        if (in[u] > in[v]) swap(u, v);

        if (int anc = lca(u, v); u == anc)
            q[i].l = in[u], q[i].lca = -1;
        else
            q[i].l = out[u], q[i].lca = anc;
        q[i].r = in[v] + 1, q[i].id = i;
    }

    int sq = sqrt(n - 1) + 1;
    sort(q.begin(), q.end(), [&](auto& a, auto& b) {
        if (a.l / sq != b.l / sq) return a.l < b.l;
        return a.l / sq & 1 ? a.r > b.r : a.r < b.r;
    });

    fill(vt.begin(), vt.end(), 0);
    vector<bool> visited(n);
    int res = 0;
    auto check = [&](int node) {
        if (visited[node]) {
            if (--vt[a[node]] == 0) --res;
        } else {
            if (++vt[a[node]] == 1) ++res;
        }
        visited[node].flip();
    };

    vector<int> ans(m);
    int pl = q[0].l, pr = q[0].l;
    for (const auto [l, r, lca, id] : q) {
        while (l < pl) check(tour[--pl]);
        while (pr < r) check(tour[pr++]);
        while (pl < l) check(tour[pl++]);
        while (r < pr) check(tour[--pr]);

        if (~lca) check(lca);
        ans[id] = res;
        if (~lca) check(lca);
    }

    for (const auto x : ans)
        cout << x << '\n';
}