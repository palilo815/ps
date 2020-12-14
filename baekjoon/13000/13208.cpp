#include <bits/stdc++.h>
using namespace std;

const int mxN = 5e2;
const int mxPair = mxN * (mxN - 1);

vector<int> adj[mxN], child[mxPair];
pair<int, int> pos[mxPair];
int c[mxN], idx[mxN][mxN], rev[mxPair], par[mxPair], ans[mxPair];

inline int find(int u) {
    while (par[u] >= 0) u = par[u];
    return u;
}
void update(int root, int u, int w) {
    if (!ans[u] && find(rev[u]) == root) ans[u] = ans[rev[u]] = w;
    for (int& v : child[u])
        update(root, v, w);
}
void merge(int u, int v, int w) {
    u = find(u), v = find(v);
    if (u == v) return;

    if (par[u] > par[v]) swap(u, v);
    par[u] += par[v];
    par[v] = u;

    child[u].emplace_back(v);
    update(u, v, w);
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(9);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; ++i)
        cin >> c[i];
    for (int u, v; m--;) {
        cin >> u >> v;
        --u, --v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    int k = n * (n - 1);
    for (int i = 0, sz = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (i != j)
                pos[sz++] = {i, j};

    sort(pos, pos + k, [&](auto& a, auto& b) {
        return c[a.first] * c[a.second] < c[b.first] * c[b.second];
    });

    for (int i = 0; i < k; ++i)
        idx[pos[i].first][pos[i].second] = i;

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (i != j)
                rev[idx[i][j]] = idx[j][i];

    memset(par, -1, sizeof(int) * k);
    for (int i = 0; i < k; ++i) {
        int w = c[pos[i].first] * c[pos[i].second];
        for (int& x : adj[pos[i].first])
            if (c[x] * c[pos[i].second] <= w)
                merge(i, idx[x][pos[i].second], w);
        for (int& x : adj[pos[i].second])
            if (c[x] * c[pos[i].first] <= w)
                merge(i, idx[pos[i].first][x], w);
    }

    int l;
    cin >> l;
    for (int u, v; l--;) {
        cin >> u >> v;
        cout << ans[idx[u - 1][v - 1]] << '\n';
    }
}