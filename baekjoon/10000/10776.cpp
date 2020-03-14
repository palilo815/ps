#include <bits/stdc++.h>
using namespace std;
typedef tuple<int, int, int> tup;

const int max_N = 2000;
const int max_K = 200;

vector<tup> adj[max_N + 1];
int dist[max_N + 1][max_K];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int K, N, M; cin >> K >> N >> M;
    while (M--) {
        int u, v, t, h; cin >> u >> v >> t >> h;
        adj[u].emplace_back(t, h, v);
        adj[v].emplace_back(t, h, u);
    }
    int src, dst; cin >> src >> dst;

    for (int i = 1; i <= N; ++i)
        fill(dist[i], dist[i] + K, INT_MAX);
    dist[src][0] = 0;

    priority_queue<tup, vector<tup>, greater<tup>> pq;
    pq.emplace(0, 0, src);

    int ans = -1;
    while (!pq.empty()) {
        auto [d, h, u] = pq.top(); pq.pop();
        if (dist[u][h] < d) continue;
        if (u == dst) { ans = d; break; }

        for (auto [w1, w2, v] : adj[u]) {
            int D = d + w1, H = h + w2;
            if (H < K && dist[v][H] > D) {
                dist[v][H] = D;
                pq.emplace(D, H, v);
            }
        }
    }
    cout << ans;
    return 0;
}