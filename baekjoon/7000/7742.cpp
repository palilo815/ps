#include <bits/stdc++.h>
using namespace std;
using p = pair<int, int>;

const int max_N = 100001;

vector<p> adj[max_N];
int dist[max_N];

int N, Q, t;
int sz[max_N], par[max_N], top[max_N], idx[max_N];
int fenwick[max_N];

void update(int i, int v) {
    for (; i <= N; i += i & -i)
        fenwick[i] += v;
}
int read(int i) {
    int ret = 0;
    for (; i; i -= i & -i)
        ret += fenwick[i];
    return ret;
}
int dfs(int u, int p) {
    for (auto& [w, v] : adj[u])
        if (v ^ p) {
            dist[v] = w;
            sz[u] += dfs(v, u);
        }
    return ++sz[u];
}
void hld(int u, int p) {
    int H = 0;
    for (auto& [w, v] : adj[u])
        if (v ^ p && sz[v] > sz[H])
            H = v;
    for (auto& [w, v] : adj[u])
        if (v ^ p && v ^ H)
            hld(v, u);

    if (!top[u]) top[u] = u;
    if (H) top[H] = top[u], hld(H, u);

    par[u] = p;
    update(idx[u] = ++t, dist[u]);
}
int solve(int u, int v) {
    int ret = 0;
    while (top[u] ^ top[v]) {
        int& n = sz[top[u]] < sz[top[v]] ? u : v;
        ret += read(idx[top[n]]) - read(idx[n] - 1);
        n = par[top[n]];
    }
    if (idx[u] > idx[v]) swap(u, v);
    ret += read(idx[v] - 1) - read(idx[u] - 1);
    return ret;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    cin >> N >> Q;
    for (int i = 1, u, v, w; i < N; ++i) {
        cin >> u >> v >> w;
        adj[u].emplace_back(w, v);
        adj[v].emplace_back(w, u);
    }

    dfs(1, 0);
    hld(1, 0);

    for (int i = 0, u, v; i < Q; ++i) {
        cin >> u >> v;
        cout << solve(u, v) << '\n';
    }
    return 0;
}