#include <bits/stdc++.h>
using namespace std;

const int max_N = 100001;

int eu[max_N], ev[max_N], ew[max_N];
vector<int> adj[max_N];

int N, t = -1;
int sz[max_N], par[max_N], top[max_N], idx[max_N];
int segT[max_N - 1 << 1];

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
void init() {
    for (int i = 1; i < N; ++i) {
        if (par[ev[i]] == eu[i]) swap(eu[i], ev[i]);
        segT[idx[eu[i]] + N] = ew[i];
    }
    for (int i = N - 1; i; --i)
        segT[i] = max(segT[i << 1], segT[i << 1 | 1]);
}
void update(int i, int v) {
    for (segT[i += N] = v; i > 1; i >>= 1)
        segT[i >> 1] = max(segT[i], segT[i ^ 1]);
}
int query(int l, int r) {
    int ret = 0;
    for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
        if (l & 1) ret = max(ret, segT[l++]);
        if (r & 1) ret = max(ret, segT[--r]);
    }
    return ret;
}
int solve(int u, int v) {
    int ret = 0;
    while (top[u] ^ top[v]) {
        int& n = sz[top[u]] < sz[top[v]] ? u : v;
        ret = max(ret, query(idx[n], idx[top[n]] + 1));
        n = par[top[n]];
    }
    if (idx[u] > idx[v]) swap(u, v);
    ret = max(ret, query(idx[u], idx[v]));
    return ret;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    cin >> N;
    for (int i = 1; i < N; ++i) {
        cin >> eu[i] >> ev[i] >> ew[i];
        adj[eu[i]].emplace_back(ev[i]);
        adj[ev[i]].emplace_back(eu[i]);
    }

    dfs(1, 0);
    hld(1, 0);
    init();

    int M; cin >> M;
    while (M--) {
        int q, a, b; cin >> q >> a >> b;
        if (q == 1) update(idx[eu[a]], b);
        else cout << solve(a, b) << '\n';
    }
    return 0;
}