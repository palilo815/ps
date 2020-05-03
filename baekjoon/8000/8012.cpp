#include <bits/stdc++.h>
using namespace std;

const int M = 30001;

vector<int> adj[M];
int sz[M], parent[M];

int chain_num[M], chain_idx[M];
int depth[M];

int DFS(int u, int p) {
    parent[u] = p;
    sz[u] = 1;
    for (int v : adj[u]) if (v != p)
        sz[u] += DFS(v, u);
    return sz[u];
}
void HLD(int u, int p, int ch_n, int ch_idx, int d) {
    depth[u] = d;
    chain_num[u] = ch_n;
    chain_idx[u] = ch_idx;

    int H = -1;
    for (int v : adj[u]) if (v != p)
        if (H == -1 || sz[v] > sz[H])
            H = v;

    if (H != -1)
        HLD(H, u, ch_n, ch_idx + 1, d);
    for (int v : adj[u]) if (v != p && v != H)
        HLD(v, u, v, 0, d + 1);
}
int query(int u, int v) {
    int ret = 0;
    while (chain_num[u] != chain_num[v]) {
        if (depth[u] > depth[v]) {
            ret += chain_idx[u] + 1;
            u = parent[chain_num[u]];
        }
        else {
            ret += chain_idx[v] + 1;
            v = parent[chain_num[v]];
        }
    }
    ret += abs(chain_idx[u] - chain_idx[v]);
    return ret;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    for (int i = 1; i < N; ++i) {
        int u, v; cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    DFS(1, 0);
    HLD(1, 0, 1, 0, 0);

    int u = 1, ans = 0;
    int Q; cin >> Q;
    while (Q--) {
        int v; cin >> v;
        ans += query(u, v);
        u = v;
    }
    cout << ans;
    return 0;
}