#include <bits/stdc++.h>
using namespace std;
struct edge {
    int v, w, dp;
    edge(int v, int w, int dp): v(v), w(w), dp(dp) {}
};

const int mxN = 5e4 + 1;

vector<edge> adj[mxN];

int solve(int u, int p) {
    int ret = 0;
    for (auto& [v, w, dp] : adj[u]) {
        if (v == p) continue;
        if (dp == 0) dp = solve(v, u) + w;
        if (dp > ret) ret = dp;
    }
    return ret;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    for (int i = 0, u, v, w; i < N - 1; ++i) {
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w, 0);
        adj[v].emplace_back(u, w, 0);
    }

    for (int i = 1; i <= N; ++i)
        cout << solve(i, 0) << '\n';
    return 0;
}