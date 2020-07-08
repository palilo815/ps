#include <bits/stdc++.h>
using namespace std;

const int max_N = 100001;

int N, Q, e[max_N];
vector<int> adj[max_N];
int t, sz[max_N], par[max_N], top[max_N], idx[max_N];
int fenwick[max_N];

void update(int i, int v) {
    for (; i <= N; i += i & -i)
        fenwick[i] ^= v;
}
int read(int i) {
    int ret = 0;
    for (; i; i -= i & -i)
        ret ^= fenwick[i];
    return ret;
}
int dfs(int u, int p) {
    for (int& v : adj[u])
        if (v ^ p)
            sz[u] += dfs(v, u);
    return ++sz[u];
}
void hld(int u, int p) {
    int H = 0;
    for (int& v : adj[u])
        if (v ^ p && sz[v] > sz[H])
            H = v;
    for (int& v : adj[u])
        if (v ^ p && v ^ H)
            hld(v, u);

    if (!top[u]) top[u] = u;
    if (H) top[H] = top[u], hld(H, u);

    par[u] = p, idx[u] = ++t;
}
int query(int u, int v) {
    int ret = 0;
    while (top[u] ^ top[v]) {
        int& n = sz[top[u]] < sz[top[v]] ? u : v;
        ret ^= read(idx[n] - 1) ^ read(idx[top[n]]);
        n = par[top[n]];
    }
    if (idx[u] > idx[v]) swap(u, v);
    ret ^= read(idx[u] - 1) ^ read(idx[v]);
    return ret;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    cin >> N >> Q;
    for (int i = 1; i <= N; ++i)
        cin >> e[i];
    for (int i = 1, u, v; i < N; ++i) {
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    dfs(1, 0);
    hld(1, 0);

    for (int i = 1; i <= N; ++i)
        update(idx[i], e[i]);

    for (int i = 0, q, u, v; i < Q; ++i) {
        cin >> q >> u >> v;
        if (q == 1) {
            int x = e[u] ^ v;
            e[u] = v;
            update(idx[u], x);
        }
        else cout << query(u, v) << '\n';
    }
    return 0;
}