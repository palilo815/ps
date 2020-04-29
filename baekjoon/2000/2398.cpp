#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> p;

const int max_N = 1000;

vector<p> adj[max_N + 1];
int dist[3][max_N + 1];
int parent[3][max_N + 1];

void Dijkstra(int src, int N, int dist[], int parent[]) {
    memset(dist, 0x3f, sizeof(int) * (N + 1));
    dist[src] = 0;

    priority_queue<p, vector<p>, greater<p>> pq;
    pq.emplace(0, src);

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (dist[u] < d) continue;

        for (auto [w, v] : adj[u]) {
            int D = d + w;
            if (dist[v] > D) {
                dist[v] = D;
                parent[v] = u;
                pq.emplace(D, v);
            }
        }
    }
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, M; cin >> N >> M;
    while (M--) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].emplace_back(w, v);
        adj[v].emplace_back(w, u);
    }

    for (int i = 0; i < 3; ++i) {
        int src; cin >> src;
        Dijkstra(src, N, dist[i], parent[i]);
    }

    int min_d = INT_MAX, dst = 0;
    for (int i = 1; i <= N; ++i) {
        int d = dist[0][i] + dist[1][i] + dist[2][i];
        if (d < min_d) min_d = d, dst = i;
    }

    vector<p> path;
    for (int i = 0; i < 3; ++i) {
        int cur = dst;
        while (parent[i][cur]) {
            path.emplace_back(parent[i][cur], cur);
            cur = parent[i][cur];
        }
    }

    cout << min_d << ' ' << path.size() << '\n';
    for (auto [u, v] : path) cout << u << ' ' << v << '\n';
    return 0;
}