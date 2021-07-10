#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n);
    for (int u, v, i = n - 1; i--;) {
        cin >> u >> v, --u, --v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    vector<int> dist(n, -1), dp(n);
    queue<int> q;
    for (int i = 0, s; i < m; ++i) {
        cin >> s, --s;
        q.emplace(s);
        dist[s] = 0, dp[s] = 1;
    }
    while (!q.empty()) {
        const auto u = q.front();
        q.pop();
        for (const auto& v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                dp[v] = dp[u];
                q.emplace(v);
            } else if (dist[v] == dist[u] + 1) {
                dp[v] += dp[u];
            }
        }
    }
    const auto it = find(dp.begin(), dp.end(), m);
    if (it == dp.end()) {
        cout << "NO";
    } else {
        cout << "YES\n";
        cout << it - dp.begin() + 1;
    }
}