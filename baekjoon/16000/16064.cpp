#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e3 + 1;

vector<pair<int, int>> adj[mxN];
int dp[mxN];

void solve(int u) {
    dp[u] = 0;
    for (auto& [v, w] : adj[u]) {
        if (dp[v] == -1) solve(v);
        dp[u] = max(dp[u], dp[v] + w);
    }
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N, M;
    cin >> N >> M;

    for (int u, v, w; M--;) {
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
    }

    memset(dp + 1, -1, sizeof(int) * N);
    for (int i = 1; i <= N; ++i)
        if (dp[i] == -1)
            solve(i);

    cout << *max_element(dp + 1, dp + N + 1);
    return 0;
}