#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int max_N = 100001;

vector<int> adj[max_N];

int N, Q, t;
int sz[max_N], par[max_N], top[max_N], idx[max_N];
ll fen1[max_N], fen2[max_N];

void update(ll fenwick[], int i, int v) {
    for (; i <= N; i += i & -i)
        fenwick[i] += v;
}
void update_range(int l, int r) {
    update(fen1, l, 1), update(fen1, r + 1, -1);
    update(fen2, l, l - 1), update(fen2, r + 1, -r);
}
ll read(ll fenwick[], int i) {
    ll ret = 0;
    for (; i; i -= i & -i)
        ret += fenwick[i];
    return ret;
}
ll read_range(int l, int r) {
    return read(fen1, r) * r - read(fen2, r) -
           read(fen1, l - 1) * (l - 1) + read(fen2, l - 1);
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
void query_P(int u, int v) {
    while (top[u] ^ top[v]) {
        int& n = sz[top[u]] < sz[top[v]] ? u : v;
        update_range(idx[n], idx[top[n]]);
        n = par[top[n]];
    }
    if (idx[u] > idx[v]) swap(u, v);
    update_range(idx[u], idx[v] - 1);
}
ll query_Q(int u, int v) {
    ll ret = 0;
    while (top[u] ^ top[v]) {
        int& n = sz[top[u]] < sz[top[v]] ? u : v;
        ret += read_range(idx[n], idx[top[n]]);
        n = par[top[n]];
    }
    if (idx[u] > idx[v]) swap(u, v);
    ret += read_range(idx[u], idx[v] - 1);
    return ret;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    cin >> N >> Q;
    for (int i = 1, u, v; i < N; ++i) {
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    dfs(1, 0);
    hld(1, 0);

    char q;
    for (int i = 0, u, v; i < Q; ++i) {
        cin >> q >> u >> v;
        if (q == 'P') query_P(u, v);
        else cout << query_Q(u, v) << '\n';
    }
    return 0;
}