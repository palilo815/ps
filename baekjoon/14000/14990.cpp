#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e3;

struct edge {
    int i, u, v, w;
};

vector<pair<int, int>> adj[mxN];
int par[mxN], idx[mxN];
bool used[mxN], passed[mxN];
edge e[mxN];

int _find(int u) {
    return par[u] < 0 ? u : (par[u] = _find(par[u]));
}
bool _union(int u, int v) {
    u = _find(u), v = _find(v);
    if (u == v) return false;

    if (par[u] > par[v]) swap(u, v);
    par[u] += par[v];
    par[v] = u;
    return true;
}
void dfs(int u, int p) {
    for (auto& [i, v] : adj[u])
        if (v != p) {
            par[v] = u, idx[v] = i;
            dfs(v, u);
        }
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N, M;
    cin >> N >> M;

    for (int i = 0; i < M; ++i)
        cin >> e[i].u >> e[i].v >> e[i].w;
    for (int i = 0; i < M; ++i)
        e[i].i = i;

    sort(e, e + M, [&](auto& a, auto& b) {
        return a.w > b.w;
    });

    memset(par, -1, sizeof(int) * N);

    for (int i = 0; i < M; ++i)
        if (_union(e[i].u, e[i].v)) {
            adj[e[i].u].emplace_back(e[i].i, e[i].v);
            adj[e[i].v].emplace_back(e[i].i, e[i].u);
        }

    dfs(0, -1);

    passed[0] = true;
    for (int i = N - 1; i; i = par[i])
        used[idx[i]] = true, passed[i] = true;

    for (int i = 0; i < M; ++i)
        if (!passed[e[i].u] && !passed[e[i].v])
            used[e[i].i] = true;

    bool none = true;
    for (int i = 0; i < M; ++i)
        if (!used[i]) {
            cout << i << ' ';
            none = false;
        }
    if (none) cout << "none";
}