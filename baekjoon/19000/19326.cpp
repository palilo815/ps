#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e5;

struct elem {
    int u, v, lca;
};

vector<int> adj[mxN + 1];
int n, t, sz[mxN + 1], par[mxN + 1], top[mxN + 1], in[mxN + 1];
elem q[mxN];
bool segT[mxN << 1];

void dfs(int u) {
    sz[u] = 1;
    for (int i = 0; i < adj[u].size(); ++i) {
        if (adj[u][i] == par[u]) {
            swap(adj[u][i], adj[u].back());
            adj[u].pop_back();
            --i;
            continue;
        }

        par[adj[u][i]] = u;
        dfs(adj[u][i]);
        sz[u] += sz[adj[u][i]];

        if (sz[adj[u][i]] > sz[adj[u][0]])
            swap(adj[u][i], adj[u][0]);
    }
}
void hld(int u) {
    in[u] = t++;
    bool heavy = true;
    for (int& v : adj[u]) {
        top[v] = heavy ? top[u] : v;
        hld(v);
        heavy = false;
    }
}
void get_lca(elem& q) {
    int u = q.u, v = q.v;
    while (top[u] != top[v])
        sz[top[u]] < sz[top[v]] ? u = par[top[u]] : v = par[top[v]];
    q.lca = in[u] < in[v] ? u : v;
}
bool query(int l, int r) {
    for (l += n, r += n; l != r; l >>= 1, r >>= 1) {
        if (l & 1 && segT[l++]) return true;
        if (r & 1 && segT[--r]) return true;
    }
    return false;
}
void choose(int u) {
    for (int i = in[u] + n; i; i >>= 1)
        segT[i] = true;
}
bool chosen(elem& q) {
    int u = q.u, v = q.v;
    for (; top[u] != top[v]; u = par[top[u]]) {
        if (sz[top[u]] > sz[top[v]]) swap(u, v);
        if (query(in[top[u]], in[u] + 1)) return true;
    }
    if (in[u] > in[v]) swap(u, v);
    return query(in[u], in[v] + 1);
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    cin >> n;
    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    top[1] = 1;
    dfs(1);
    hld(1);

    int m;
    cin >> m;

    for (int i = 0; i < m; ++i)
        cin >> q[i].u >> q[i].v;

    for (int i = 0; i < m; ++i)
        get_lca(q[i]);

    sort(q, q + m, [&](auto& a, auto& b) {
        return sz[top[a.lca]] == sz[top[b.lca]] ? in[a.lca] > in[b.lca] : sz[top[a.lca]] < sz[top[b.lca]];
    });

    vector<int> ans;
    for (int i = 0; i < m; ++i) {
        if (chosen(q[i])) continue;
        ans.emplace_back(q[i].lca);
        choose(q[i].lca);
    }

    cout << ans.size() << '\n';
    for (int& x : ans) cout << x << ' ';
}