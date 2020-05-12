#include <bits/stdc++.h>
using namespace std;

const int max_N = 101;
const int max_K = 501;
const int INF = 0x3f3f3f3f;

int h[max_N];
vector<int> adj[max_N];
int DP[max_N][max_K];

int solve(int u, int k) {
    if (k == 0) return h[u];
    int& ret = DP[u][k];
    if (ret != INF) return ret;

    for (int v : adj[u])
        ret = min(ret, solve(v, k - 1));
    return ret;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, M; cin >> N >> M;
    for (int i = 1; i <= N; ++i)
        cin >> h[i];
    while (M--) {
        int u, v; cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    memset(DP, 0x3f, sizeof(DP));

    int T; cin >> T;
    while (T--) {
        int u, k; cin >> u >> k;
        int ans = solve(u, k);
        cout << (ans == INF ? -1 : ans) << '\n';
    }
    return 0;
}