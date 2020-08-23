#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e5 + 1;

vector<int> adj[mxN];
int D, dist[mxN];

void dfs(int u, int p) {
    for (int& v : adj[u])
        if (v ^ p) {
            dfs(v, u);
            dist[u] = max(dist[u], dist[v] + 1);
        }
}
int solve(int u, int p) {
    int ret = 0;
    for (int& v : adj[u])
        if (v ^ p && dist[v] >= D)
            ret += solve(v, u) + 1;
    return ret;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, S; cin >> N >> S >> D;
    for (int i = 1, u, v; i ^ N; ++i) {
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    dfs(S, 0);

    cout << solve(S, 0) * 2;
    return 0;
}