#include <bits/stdc++.h>
using namespace std;

const int max_N = 100001;

int N, M, cow[max_N];
vector<int> adj[max_N];
int t = -1, sz[max_N], par[max_N], top[max_N], idx[max_N];
vector<int> segT[max_N - 1 << 1];

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
    for (int i = 1; i <= N; ++i)
        segT[idx[i] + N] = {cow[i]};
    for (int i = N - 1; i; --i) {
        segT[i].resize(segT[i << 1].size() + segT[i << 1 | 1].size());
        segT[i].resize(set_union(segT[i << 1].begin(), segT[i << 1].end(), segT[i << 1 | 1].begin(), segT[i << 1 | 1].end(), segT[i].begin()) - segT[i].begin());
    }
}
bool query(int l, int r, int q) {
    for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
        if (l & 1) {
            if (binary_search(segT[l].begin(), segT[l].end(), q)) return '1';
            ++l;
        }
        if (r & 1) {
            --r;
            if (binary_search(segT[r].begin(), segT[r].end(), q)) return '1';
        }
    }
    return false;
}
char solve(int u, int v, int q) {
    while (top[u] ^ top[v]) {
        int& n = sz[top[u]] < sz[top[v]] ? u : v;
        if (query(idx[n], idx[top[n]] + 1, q)) return '1';
        n = par[top[n]];
    }
    if (idx[u] > idx[v]) swap(u, v);
    if (query(idx[u], idx[v] + 1, q)) return '1';
    return '0';
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    cin >> N >> M;
    for (int i = 1; i <= N; ++i)
        cin >> cow[i];
    for (int i = 1, u, v; i < N; ++i) {
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    dfs(1, 0);
    hld(1, 0);
    init();

    for (int i = 0, u, v, q; i < M; ++i) {
        cin >> u >> v >> q;
        cout << solve(u, v, q);
    }
    return 0;
}