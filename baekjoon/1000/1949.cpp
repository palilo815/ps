#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e4 + 1;

vector<int> adj[mxN];
int dp[mxN][2];

void solve(int u, int p) {
    for (int& v : adj[u]) {
        if (v == p) continue;
        solve(v, u);
        dp[u][0] += max(dp[v][0], dp[v][1]);
        dp[u][1] += dp[v][0];
    }
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    for (int i = 1; i <= N; ++i)
        cin >> dp[i][1];
    for (int i = 1, u, v; i < N; ++i) {
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    solve(1, 0);
    cout << max(dp[1][0], dp[1][1]);
    return 0;
}