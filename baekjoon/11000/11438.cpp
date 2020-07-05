#include <bits/stdc++.h>
using namespace std;

const int max_N = 100001;

vector<int> adj[max_N];

int sz[max_N], par[max_N], dep[max_N], top[max_N], idx[max_N];

int dfs(int u, int p) {
    par[u] = p, sz[u] = 1;
    for (int& v : adj[u])
        if (v ^ p)
            sz[u] += dfs(v, u);
    return sz[u];
}
void hld(int u, int p, int rt, int i, int d) {
    dep[u] = d, top[u] = rt, idx[u] = i;
    int H = -1;
    for (int& v : adj[u])
        if (v ^ p && (H == -1 || sz[v] > sz[H]))
            H = v;

    if (~H) hld(H, u, rt, i + 1, d);
    for (int& v : adj[u])
        if (v ^ p && v ^ H)
            hld(v, u, v, 0, d + 1);
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

    dfs(1, 0);
    hld(1, 0, 1, 0, 0);

    int Q; cin >> Q;
    while (Q--) {
        int u, v; cin >> u >> v;
        while (top[u] ^ top[v])
            dep[u] < dep[v] ? (v = par[top[v]]) : (u = par[top[u]]);
        cout << (idx[u] < idx[v] ? u : v) << '\n';
    }
    return 0;
}