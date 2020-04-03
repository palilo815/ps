#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> p;

const int max_N = 300;

vector<p> adj[max_N + 1];
int DP[max_N + 1][max_N + 1];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, M, K; cin >> N >> M >> K;
    while (K--) {
        int u, v, w; cin >> u >> v >> w;
        if (u < v) adj[u].emplace_back(w, v);
    }

    memset(DP, -1, sizeof(DP));
    DP[1][1] = 0;

    for (int u = 1; u < N; ++u)
        for (int i = min(u, M - 1); i >= 0; --i) {
            if (DP[u][i] == -1) continue;
            for (auto [w, v] : adj[u])
                DP[v][i + 1] = max(DP[v][i + 1], DP[u][i] + w);
        }

    int ans = 0;
    for (int i = 1; i <= M; ++i)
        ans = max(ans, DP[N][i]);
    cout << ans;
    return 0;
}