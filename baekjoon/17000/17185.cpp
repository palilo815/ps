#include <bits/stdc++.h>
#define left (i << 1)
#define right (i << 1 | 1)
using namespace std;

const int mxN = 1e5 + 1;
const int64_t INF = 0x3f3f3f3f3f3f3f3f;

struct edge {
    int u, v, w;
};

vector<pair<int, int>> adj[mxN];
edge e[mxN - 1];
int t, sz[mxN], par[mxN], top[mxN], in[mxN], out[mxN];
bool shop[mxN];
int64_t dep[mxN], segT[mxN << 1];

void dfs(int u) {
    sz[u] = 1;
    for (int i = 0; i < adj[u].size(); ++i) {
        if (adj[u][i].second == par[u]) {
            swap(adj[u][i], adj[u].back());
            adj[u].pop_back();
            --i;
            continue;
        }

        par[adj[u][i].second] = u;
        dfs(adj[u][i].second);
        sz[u] += sz[adj[u][i].second];

        if (sz[adj[u][i].second] > sz[adj[u][0].second])
            swap(adj[u][i], adj[u][0]);
    }
}
int64_t hld(int u) {
    in[u] = t++;
    int64_t dp = shop[u] ? -dep[u] : INF;

    bool heavy = true;
    for (auto& [w, v] : adj[u]) {
        top[v] = heavy ? top[u] : v;
        dep[v] = dep[u] + w;
        dp = min(dp, hld(v) + (w << 1));
        heavy = false;
    }

    out[u] = t;
    return segT[in[u]] = dp;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N, S, Q, E;
    cin >> N >> S >> Q >> E;

    for (int i = 1; i < N; ++i) {
        cin >> e[i].u >> e[i].v >> e[i].w;
        adj[e[i].u].emplace_back(e[i].w, e[i].v);
        adj[e[i].v].emplace_back(e[i].w, e[i].u);
    }

    for (int u; S--;) {
        cin >> u;
        shop[u] = true;
    }

    t = N;
    top[E] = E;

    dfs(E);
    hld(E);

    for (int i = 1; i < N; ++i)
        if (par[e[i].u] == e[i].v)
            swap(e[i].u, e[i].v);

    for (int i = N - 1; i; --i)
        segT[i] = min(segT[left], segT[right]);

    for (int road, home; Q--;) {
        cin >> road >> home;
        int root = e[road].v;

        if (in[home] < in[root] || out[root] <= in[home]) {
            cout << "escaped\n";
            continue;
        }

        int64_t ans = INF, d = dep[home];
        auto query = [&](int l, int r) {
            for (; l != r; l >>= 1, r >>= 1) {
                if (l & 1) ans = min(ans, segT[l++]);
                if (r & 1) ans = min(ans, segT[--r]);
            }
        };

        for (; top[home] != top[root]; home = par[top[home]])
            query(in[top[home]], in[home] + 1);
        query(in[root], in[home] + 1);

        if (ans == INF)
            cout << "oo\n";
        else
            cout << ans + d << '\n';
    }
}