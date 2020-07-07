#include <bits/stdc++.h>
using namespace std;
using p = pair<int, int>;
using ll = long long;

const int max_N = 200001;

struct edge {
    int u, v, w, i;
} e[max_N];
vector<p> adj[max_N];

int N, M, t = -1;
int sz[max_N], par[max_N], top[max_N], idx[max_N];
int segT[max_N - 1 << 1];

int parent[max_N];
bool used[max_N];
ll ans[max_N];

int _find(int u) {
    if (parent[u] < 0) return u;
    return parent[u] = _find(parent[u]);
}
int dfs(int u, int p) {
    for (auto& [w, v] : adj[u])
        if (v ^ p)
            sz[u] += dfs(v, u);
    return ++sz[u];
}
void hld(int u, int p, int d) {
    int H = 0, HD = 0;
    for (auto& [w, v] : adj[u])
        if (v ^ p && sz[v] > sz[H])
            H = v, HD = w;
    for (auto& [w, v] : adj[u])
        if (v ^ p && v ^ H)
            hld(v, u, w);

    if (!top[u]) top[u] = u;
    if (H) top[H] = top[u], hld(H, u, HD);

    par[u] = p, idx[u] = ++t;
    segT[idx[u] + N] = d;
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
ll build_mst() {
    memset(parent + 1, -1, sizeof(int) * N);
    sort(e, e + M, [&](edge & a, edge & b) -> bool {
        return a.w < b.w;
    });

    ll mst = 0;
    for (int j = 0; j < M; ++j) {
        auto [u, v, w, i] = e[j];
        u = _find(u), v = _find(v);
        if (u ^ v) {
            mst += w, parent[u] = v, used[i] = true;
            adj[u].emplace_back(w, v);
            adj[v].emplace_back(w, u);
        }
    }
    return mst;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    cin >> N >> M;
    for (int i = 0; i < M; ++i) {
        cin >> e[i].u >> e[i].v >> e[i].w;
        e[i].i = i;
    }

    ll mst = build_mst();
    dfs(1, 0);
    hld(1, 0, 0);

    for (int i = N - 1; i; --i)
        segT[i] = max(segT[i << 1], segT[i << 1 | 1]);

    for (int j = 0; j < M; ++j) {
        auto& [u, v, w, i] = e[j];
        ans[i] = used[i] ? mst : mst + w - solve(u, v);
    }
    for (int i = 0; i < M; ++i) cout << ans[i] << '\n';
    return 0;
}