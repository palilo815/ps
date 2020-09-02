#include <bits/stdc++.h>
using namespace std;

const int mxN = 2e4 + 1;

vector<pair<int, int>> adj[mxN];
vector<int> vt;
int dp[mxN], par[mxN], nxt[mxN];
bool visited[mxN];

void dfs(int u) {
    visited[u] = true;
    for (auto& [w, v] : adj[u])
        if (!visited[v] && v ^ par[u]) {
            par[v] = u;
            dfs(v);
        }
    vt.emplace_back(u);
}
void solve() {
    int N, E; cin >> N >> E;

    for (int i = 1; i <= N; ++i)
        adj[i].clear();
    vt.clear();
    memset(visited + 1, 0, N);
    memset(nxt + 1, 0, sizeof(int) * N);

    for (int i = 1; i <= N; ++i)
        cin >> dp[i];
    for (int u, v, w; E; --E) {
        cin >> u >> v >> w;
        adj[u].emplace_back(w, v);
    }

    dfs(1);

    for (int& u : vt) {
        int mx = 0;
        for (auto& [w, v] : adj[u])
            if (v ^ par[u] && dp[v] - w > mx) {
                mx = dp[v] - w;
                nxt[u] = v;
            }
        dp[u] += mx;
    }

    vector<int> path;
    for (int i = 1; i; i = nxt[i])
        path.emplace_back(i);

    cout << dp[1] << ' ' << path.size() << '\n';
    for (int& x : path) cout << x << ' ';
    cout << '\n';
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int T; cin >> T;
    while (T--) solve();
    return 0;
}