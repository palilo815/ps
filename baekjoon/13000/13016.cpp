#include <bits/stdc++.h>
using namespace std;

const int mxN = 5e4 + 1;

vector<pair<int, int>> adj[mxN];
int par[mxN], dp[mxN];

void dfs(int u) {
    int mx = 0;
    for (auto& [w, v] : adj[u]) {
        if (v == par[u]) {
            v = 0;
            continue;
        }
        par[v] = u;
        dfs(v);
        mx = max(mx, dp[v] + w);
    }
    dp[u] += mx;
}
void solve(int u, int p_val) {
    dp[u] = max(dp[u], p_val);
    if (adj[u].size() <= 2) {
        for (auto& [w, v] : adj[u])
            if (v)
                solve(v, p_val + w);
        return;
    }

    int m1 = -1, m2 = -1;
    for (auto& [w, v] : adj[u]) {
        if (dp[v] + w > m1) {
            m2 = m1;
            m1 = dp[v] + w;
        } else if (dp[v] + w > m2)
            m2 = dp[v] + w;
    }

    for (auto& [w, v] : adj[u])
        if (v)
            solve(v, w + max(p_val, dp[v] + w == m1 ? m2 : m1));
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n;
    for (int i = 1, u, v, w; i < n; ++i) {
        cin >> u >> v >> w;
        adj[u].emplace_back(w, v);
        adj[v].emplace_back(w, u);
    }

    adj[1].emplace_back(0, 0);
    dfs(1);
    solve(1, 0);

    for (int i = 1; i <= n; ++i)
        cout << dp[i] << '\n';
}