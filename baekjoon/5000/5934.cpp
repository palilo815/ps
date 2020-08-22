#include <bits/stdc++.h>
using namespace std;

const int mxN = 5e4 + 1;

vector<int> adj[mxN];
int cnt[mxN];
bool dp[mxN];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    for (int i = 1, u, v; i ^ N; ++i) {
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
        ++cnt[u], ++cnt[v];
    }

    queue<pair<int, int>> q;
    for (int i = 1; i <= N; ++i)
        if (cnt[i] == 1)
            q.emplace(i, 0);

    int ans = 0;
    while (!q.empty()) {
        auto [u, p] = q.front(); q.pop();
        bool visit = !dp[u];

        if (visit) ++ans;
        for (int& v : adj[u])
            if (v ^ p) {
                if (visit) dp[v] = true;
                if (--cnt[v] == 1) q.emplace(v, u);
            }
    }
    cout << ans;
    return 0;
}