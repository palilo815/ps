#include <bits/stdc++.h>
using namespace std;

const int mxN = 5e5;

vector<int> adj[mxN];
int a[mxN];
double dp[mxN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N, M;
    cin >> N >> M;
    for (int i = 0; i < N; ++i)
        cin >> a[i];
    for (int u, v; M--;) {
        cin >> u >> v;
        adj[u].emplace_back(v);
    }

    vector<bool> visited(N);
    vector<int> vt;
    function<void(int)> dfs = [&](int u) {
        visited[u] = true;
        for (int& v : adj[u])
            if (!visited[v])
                dfs(v);
        vt.emplace_back(u);
    };

    for (int i = 0; i < N; ++i)
        if (!visited[i])
            dfs(i);

    for (auto& u : vt) {
        double mx = 0;
        for (int& v : adj[u])
            mx = max(mx, dp[v]);
        dp[u] = max(a[u] + mx / 2, mx);
    }
    cout << fixed << setprecision(9) << dp[0];
    return 0;
}