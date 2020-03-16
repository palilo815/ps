#include <bits/stdc++.h>
using namespace std;
typedef tuple<int, int, int> tup;

const int max_N = 100;
const int max_M = 10000;

vector<tup> adj[max_N + 1];
int dist[max_N + 1][max_M + 1];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T, N, M, K;
    cin >> T;
    while (T--) {
        cin >> N >> M >> K;
        for (int i = 1; i <= N; ++i) {
            adj[i].clear();
            fill(dist[i], dist[i] + M + 1, INT_MAX);
        }
        while (K--) {
            int u, v, c, d; cin >> u >> v >> c >> d;
            adj[u].emplace_back(d, c, v);
        }

        dist[1][0] = 0;
        priority_queue<tup, vector<tup>, greater<tup>> pq;
        pq.emplace(0, 0, 1);

        int ans = -1;
        while (!pq.empty()) {
            auto [d, c, u] = pq.top(); pq.pop();
            if (dist[u][c] < d) continue;
            if (u == N) { ans = d; break; }

            for (auto [w1, w2, v] : adj[u]) {
                int D = d + w1, C = c + w2;
                if (C > M || dist[v][C] <= D) continue;

                for (int cost = C; cost <= M; ++cost) {
                    if (dist[v][cost] > D)
                        dist[v][cost] = D;
                    else break;
                }
                pq.emplace(D, C, v);
            }
        }

        if (ans == -1) cout << "Poor KCM";
        else cout << ans;
        cout << '\n';
    }
    return 0;
}