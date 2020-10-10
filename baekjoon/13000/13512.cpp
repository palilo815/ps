#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e5;

vector<int> adj[mxN];
set<pair<int, int>> st[mxN];
int t, sz[mxN], par[mxN], top[mxN], in[mxN];

void dfs(int u, int p) {
    sz[u] = 1, par[u] = p;
    for (int& v : adj[u]) {
        if (v == p) continue;
        dfs(v, u);
        sz[u] += sz[v];
        if (adj[u][0] == p || sz[v] > sz[adj[u][0]])
            swap(v, adj[u][0]);
    }
}
void hld(int u) {
    in[u] = t++;
    for (int& v : adj[u]) {
        if (v == par[u]) continue;
        top[v] = (v == adj[u][0] ? top[u] : v);
        hld(v);
    }
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N;
    cin >> N;
    for (int u, v; --N;) {
        cin >> u >> v;
        --u, --v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    dfs(0, -1);
    hld(0);

    int M;
    cin >> M;
    for (int q, u; M--;) {
        cin >> q >> u;
        --u;
        if (q == 1) {
            auto it = st[top[u]].find({in[u], u});
            if (it == st[top[u]].end())
                st[top[u]].emplace(in[u], u);
            else
                st[top[u]].erase(it);
        } else {
            int ans = -2;
            for (; ~u; u = par[top[u]])
                if (!st[top[u]].empty() && st[top[u]].begin()->first <= in[u])
                    ans = st[top[u]].begin()->second;
            cout << ans + 1 << '\n';
        }
    }
    return 0;
}