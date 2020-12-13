#include <bits/stdc++.h>
#define lson (i << 1)
#define rson (i << 1 | 1)
using namespace std;

const int mxN = 1e5;
const int mxM = 3e5;

struct edge {
    int u, v, w;
};

edge e[mxM];
bitset<mxM> used;
vector<pair<int, int>> adj[mxN];
int even[mxN << 1], odd[mxN << 1], *segT;
int t, sz[mxN], par[mxN], top[mxN], in[mxN];

int find(int u) {
    return par[u] < 0 ? u : par[u] = find(par[u]);
}
void dfs(int u) {
    sz[u] = 1;
    for (auto& [w, v] : adj[u]) {
        if (v == par[u]) continue;

        par[v] = u;
        dfs(v);
        sz[u] += sz[v];

        if (adj[u][0].second == par[u] || sz[v] > sz[adj[u][0].second])
            swap(w, adj[u][0].first), swap(v, adj[u][0].second);
    }
}
void hld(int u, int d) {
    (d & 1 ? odd[t] : even[t]) = d;
    in[u] = t++;
    bool heavy = true;
    for (auto& [w, v] : adj[u]) {
        if (v == par[u]) continue;

        top[v] = heavy ? top[u] : v;
        hld(v, w);
        heavy = false;
    }
}
int query(int l, int r) {
    int ret = 0;
    for (; l != r; l >>= 1, r >>= 1) {
        if (l & 1) ret = max(ret, segT[l++]);
        if (r & 1) ret = max(ret, segT[--r]);
    }
    return ret;
}
int solve(int u, int v, int w) {
    int ret = 0;
    segT = (w & 1 ? even : odd);

    for (; top[u] != top[v]; u = par[top[u]]) {
        if (sz[top[u]] > sz[top[v]]) swap(u, v);
        ret = max(ret, query(in[top[u]], in[u] + 1));
    }
    if (in[u] > in[v]) swap(u, v);
    ret = max(ret, query(in[u] + 1, in[v] + 1));
    return ret ? w - ret : INT_MAX;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; ++i) {
        cin >> e[i].u >> e[i].v >> e[i].w;
        --e[i].u, --e[i].v;
    }

    memset(par, 0xff, sizeof(int) * n);
    sort(e, e + m, [&](auto& a, auto& b) {
        return a.w < b.w;
    });

    int64_t mst1 = 0;
    for (int i = 0; i < m; ++i) {
        int u = find(e[i].u), v = find(e[i].v);
        if (u == v) continue;

        if (par[u] > par[v]) swap(u, v);
        par[u] += par[v];
        par[v] = u;

        mst1 += e[i].w;
        used[i] = true;
        adj[e[i].u].emplace_back(e[i].w, e[i].v);
        adj[e[i].v].emplace_back(e[i].w, e[i].u);
    }

    if (count_if(par, par + n, [&](auto& x) { return x < 0; }) != 1)
        return cout << "-1 -1", 0;

    par[0] = -1;
    t = n;
    dfs(0);
    hld(0, 0);

    for (int i = n - 1; i; --i)
        even[i] = max(even[lson], even[rson]);
    for (int i = n - 1; i; --i)
        odd[i] = max(odd[lson], odd[rson]);

    int add = INT_MAX;
    for (int i = 0; i < m; ++i)
        if (!used[i])
            add = min(add, solve(e[i].u, e[i].v, e[i].w));

    int64_t mst2 = add == INT_MAX ? -1 : mst1 + add;
    if (!(mst1 & 1)) swap(mst1, mst2);
    cout << mst1 << ' ' << mst2;
}