#include <bits/stdc++.h>
using namespace std;

const int M = 2e5 + 1;
const string ans[2] = {"YES\n", "NO\n"};

vector<int> adj[M];
int N, t, par[M], sz[M], top[M], idx[M];
bool segT[M << 1];

void dfs(int u) {
    sz[u] = 1;
    for (int& v : adj[u]) {
        dfs(v);
        sz[u] += sz[v];
        if (sz[v] > sz[adj[u][0]])
            swap(v, adj[u][0]);
    }
}
void hld(int u) {
    idx[u] = t++;
    for (int& v : adj[u]) {
        top[v] = v == adj[u][0] ? top[u] : v;
        hld(v);
    }
}
void update(int i) {
    for (segT[i += N] = true; i > 1; i >>= 1)
        segT[i >> 1] = segT[i] | segT[i ^ 1];
}
int query(int l, int r) {
    for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
        if (l & 1 && segT[l++]) return 1;
        if (r & 1 && segT[--r]) return 1;
    }
    return 0;
}
int solve(int u, int v) {
    while (top[u] ^ top[v]) {
        int& n = sz[top[u]] < sz[top[v]] ? u : v;
        if (query(idx[top[n]], idx[n] + 1)) return 1;
        n = par[top[n]];
    }
    if (idx[u] > idx[v]) swap(u, v);
    return query(idx[u] + 1, idx[v] + 1);
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int Q; cin >> N >> Q;
    for (int i = 2; i <= N; ++i) {
        cin >> par[i];
        adj[par[i]].emplace_back(i);
    }

    top[1] = 1;
    dfs(1);
    hld(1);

    for (int i = 0, u, v, d; i < Q; ++i) {
        cin >> u >> v >> d;
        int x = solve(u, v);
        cout << ans[x];
        if (d) x ? update(idx[v]) : update(idx[u]);
    }
    return 0;
}