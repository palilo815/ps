#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e5 + 1;

vector<int> adj[mxN];
int t, sz[mxN], par[mxN], top[mxN], dep[mxN];

void dfs(int u, int p) {
    sz[u] = 1, par[u] = p, dep[u] = dep[p] + 1;
    for (int& v : adj[u])
        if (v ^ p) {
            dfs(v, u);
            sz[u] += sz[v];
        }
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
}
int solve(int u, int v) {
    while (top[u] ^ top[v])
        sz[top[u]] < sz[top[v]] ? (u = par[top[u]]) : (v = par[top[v]]);
    return dep[u] < dep[v] ? u : v;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    for (int u, v; --N;) {
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    dfs(1, 0);
    hld(1, 0);

    cin >> N;
    for (int r, u, v; N--;) {
        cin >> r >> u >> v;
        int res[3] = {solve(u, v), solve(r, u), solve(r, v)};
        cout << *max_element(res, res + 3, [&](int& a, int& b) {
            return dep[a] < dep[b];
        }) << '\n';
    }
    return 0;
}