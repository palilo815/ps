#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e5;

vector<int> adj[mxN];
int dp[mxN];

void solve(int u) {
    dp[u] = 1;
    for (int& v : adj[u])
        if (adj[v].size() > adj[u].size()) {
            if (!dp[v]) solve(v);
            dp[u] = max(dp[u], dp[v] + 1);
        }
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, M; cin >> N >> M;
    for (int u, v; M; --M) {
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    for (int i = 0; i < N; ++i)
        if (!dp[i])
            solve(i);
    cout << *max_element(dp, dp + N);
    return 0;
}