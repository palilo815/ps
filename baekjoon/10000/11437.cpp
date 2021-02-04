#include <bits/stdc++.h>
using namespace std;

const int mxN = 5e4 + 1;

vector<int> adj[mxN];
int t, sz[mxN], par[mxN], top[mxN], in[mxN];

void dfs(int u) {
    sz[u] = 1;
    for (int i = 0; i < adj[u].size(); ++i) {
        int& v = adj[u][i];
        if (v == par[u]) {
            swap(v, adj[u].back());
            adj[u].pop_back();
            --i;
            continue;
        }

        par[v] = u;
        dfs(v);
        sz[u] += sz[v];

        if (sz[v] > sz[adj[u][0]])
            swap(v, adj[u][0]);
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
int lca(int u, int v) {
    while (top[u] != top[v])
        sz[top[u]] < sz[top[v]] ? u = par[top[u]] : v = par[top[v]];
    return in[u] < in[v] ? u : v;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N;
    cin >> N;

    for (int i = 1, u, v; i < N; ++i) {
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    top[1] = 1;
    dfs(1);
    hld(1);

    int Q;
    cin >> Q;

    for (int u, v; Q--;) {
        cin >> u >> v;
        cout << lca(u, v) << '\n';
    }
}