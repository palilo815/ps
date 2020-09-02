#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
using ll = long long;

const int mxN = 1e5 + 1;
const int mod = 1e9 + 7;

vector<int> adj[mxN];
int dp[mxN][3];

void solve(int u, int p) {
    for (int& v : adj[u]) {
        if (v == p) continue;
        solve(v, u);
        dp[u][0] = (ll)dp[u][0] * (dp[v][1] + dp[v][2]) % mod;
        dp[u][1] = (ll)dp[u][1] * (dp[v][2] + dp[v][0]) % mod;
        dp[u][2] = (ll)dp[u][2] * (dp[v][0] + dp[v][1]) % mod;
    }
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, K; cin >> N >> K;
    for (int i = 1, u, v; i < N; ++i) {
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    fill(dp[1], dp[N + 1], 1);
    for (int u, c; K; --K) {
        cin >> u >> c;
        switch (c) {
        case 1 : dp[u][1] = dp[u][2] = 0; break;
        case 2 : dp[u][2] = dp[u][0] = 0; break;
        default: dp[u][0] = dp[u][1] = 0;
        }
    }

    solve(1, 0);

    cout << ((ll)dp[1][0] + dp[1][1] + dp[1][2]) % mod;
    return 0;
}