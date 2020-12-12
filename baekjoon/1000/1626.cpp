#include <bits/stdc++.h>
#define m1 first
#define m2 second
using namespace std;
using p = pair<int, int>;

const int mxV = 5e4;
const int mxE = 2e5;

struct edge {
    int u, v, w, i;
};

edge e[mxE];
bitset<mxE> used;
p segT[mxV << 1];
vector<p> adj[mxV];
int t, sz[mxV], par[mxV], top[mxV], in[mxV];

p max2(p lhs, p rhs) {
    if (lhs.m1 > rhs.m1) return {lhs.m1, max(lhs.m2, rhs.m1)};
    if (lhs.m1 < rhs.m1) return {rhs.m1, max(rhs.m2, lhs.m1)};
    return {lhs.m1, max(lhs.m2, rhs.m2)};
}
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
    segT[t] = {d, -1};
    in[u] = t++;
    bool heavy = true;
    for (auto& [w, v] : adj[u]) {
        if (v == par[u]) continue;

        top[v] = heavy ? top[u] : v;
        hld(v, w);
        heavy = false;
    }
}
p query(int l, int r) {
    p ret = {-1, -1};
    for (; l != r; l >>= 1, r >>= 1) {
        if (l & 1) ret = max2(ret, segT[l++]);
        if (r & 1) ret = max2(ret, segT[--r]);
    }
    return ret;
}
p solve(int u, int v) {
    p ret = {-1, -1};
    for (; top[u] != top[v]; u = par[top[u]]) {
        if (sz[top[u]] > sz[top[v]]) swap(u, v);
        ret = max2(ret, query(in[top[u]], in[u] + 1));
    }
    if (in[u] > in[v]) swap(u, v);
    ret = max2(ret, query(in[u] + 1, in[v] + 1));
    return ret;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int V, E;
    cin >> V >> E;
    if (E <= V - 1) return cout << -1, 0;

    for (int i = 0; i < E; ++i) {
        cin >> e[i].u >> e[i].v >> e[i].w;
        --e[i].u, --e[i].v, e[i].i = i;
    }

    memset(par, -1, sizeof(int) * V);
    sort(e, e + E, [&](auto& a, auto& b) {
        return a.w < b.w;
    });

    int mst = 0;
    for (int i = 0; i < E; ++i) {
        auto merge = [&](edge& e) {
            int u = find(e.u), v = find(e.v);
            if (u == v) return;
            if (par[u] > par[v]) swap(u, v);
            par[u] += par[v];
            par[v] = u;
            mst += e.w;
            used[e.i] = true;
            adj[e.u].emplace_back(e.w, e.v);
            adj[e.v].emplace_back(e.w, e.u);
        };
        merge(e[i]);
    }

    if (count_if(par, par + V, [&](auto& x) { return x < 0; }) > 1)
        return cout << -1, 0;

    t = V;
    par[0] = -1;
    dfs(0);
    hld(0, 0);

    for (int i = V - 1; i; --i)
        segT[i] = max2(segT[i << 1], segT[i << 1 | 1]);

    int ans = INT_MAX;
    for (int i = 0; i < E; ++i) {
        if (used[e[i].i]) continue;
        auto [w1, w2] = solve(e[i].u, e[i].v);
        if (e[i].w != w1)
            ans = min(ans, e[i].w - w1);
        else if (~w2)
            ans = min(ans, e[i].w - w2);
    }
    cout << (ans == INT_MAX ? -1 : mst + ans);
}