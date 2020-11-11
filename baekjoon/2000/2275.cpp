#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e4;

vector<int> adj[mxN + 1];
int h[mxN + 1], dist[mxN + 1], H, ans;

void dfs(int u) {
    if (adj[u].empty()) return;
    for (int& v : adj[u]) dfs(v);
    int heavy = *max_element(adj[u].begin(), adj[u].end(), [&](auto& a, auto& b) {
        return h[a] + dist[a] < h[b] + dist[b];
    });
    h[u] = h[heavy] + dist[heavy];
}
void solve(int u) {
    for (int& v : adj[u]) {
        if (h[v] + dist[v] <= H) continue;
        if (dist[v] >= h[v] + dist[v] - H)
            ans += h[v] + dist[v] - H;
        else {
            ans += dist[v];
            solve(v);
        }
    }
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N;
    cin >> N >> H;

    for (int i = 1, p; i <= N; ++i) {
        cin >> p >> dist[i];
        adj[p].emplace_back(i);
    }

    int root = adj[0][0];
    dfs(root);
    solve(root);
    cout << ans;
}