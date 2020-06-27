#include <bits/stdc++.h>
using namespace std;
using p = pair<int, int>;

const int max_N = 50001;

vector<p> adj[max_N];
vector<p> hay;
int dist[2][max_N];
priority_queue<p, vector<p>, greater<p>> pq;

void Dijkstra(int N, int dist[]) {
    while (!pq.empty()) {
        auto[d, u] = pq.top(); pq.pop();
        if (dist[u] < d) continue;
        for (auto[w, v] : adj[u]) {
            int D = d + w;
            if (dist[v] > D) {
                dist[v] = D;
                pq.emplace(D, v);
            }
        }
    }
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, M, K; cin >> N >> M >> K;
    while (M--) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].emplace_back(w, v);
        adj[v].emplace_back(w, u);
    }
    while (K--) {
        int idx, yummy; cin >> idx >> yummy;
        hay.emplace_back(idx, yummy);
    }

    memset(dist[0] + 1, 0x3f, sizeof(int)*N);
    dist[0][N] = 0;
    pq.emplace(0, N);
    Dijkstra(N, dist[0]);

    memset(dist[1] + 1, 0x3f, sizeof(int)*N);
    for (auto&[i, yummy] : hay) {
        dist[1][i] = dist[0][i] - yummy;
        pq.emplace(dist[0][i] - yummy, i);
    }
    Dijkstra(N, dist[1]);

    for (int i = 1; i < N; ++i)
        cout << (dist[1][i] <= dist[0][i]) << '\n';
    return 0;
}