#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e3;

vector<int> adj[mxN];
int a[mxN], dp[mxN], cnt[mxN];

int solve() {
    int N, M, S;
    cin >> N >> M;

    memset(dp, 0, sizeof(int) * N);
    memset(cnt, 0, sizeof(int) * N);
    for (int i = 0; i < N; ++i)
        adj[i].clear();

    for (int i = 0; i < N; ++i)
        cin >> a[i];
    for (int u, v; M--;) {
        cin >> u >> v;
        --u, --v;
        ++cnt[u], ++cnt[v];
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    cin >> S;
    --S;

    queue<int> q;
    for (int i = 0; i < N; ++i)
        if (i ^ S && cnt[i] == 1)
            q.emplace(i);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        dp[u] += a[u];
        a[u] = cnt[u] = 0;

        for (int& v : adj[u])
            if (v ^ S && cnt[v]) {
                dp[v] = max(dp[v], dp[u]);
                if (--cnt[v] == 1)
                    q.emplace(v);
            }
    }
    return accumulate(a, a + N, 0) + *max_element(dp, dp + N);
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int T;
    cin >> T;
    for (int t = 1; t <= T; ++t)
        cout << "Data Set " << t << ":\n"
             << solve() << '\n'
             << '\n';
    return 0;
}