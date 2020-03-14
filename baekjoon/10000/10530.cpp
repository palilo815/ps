#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> p;

const int max_N = 10000;

int d1[max_N], d2[max_N];
vector<p> adj[max_N];

void Dijkstra(int dist[], int N, int src) {
    fill(dist, dist + N, INT_MAX);
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
                pq.emplace(D, v);
            }
        }
    }
}
int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, M; cin >> N >> M;
    while (M--) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].emplace_back(w, v);
        adj[v].emplace_back(w, u);
    }

    Dijkstra(d1, N, 0);
    Dijkstra(d2, N, N - 1);

    int ans = 0;
    int path = d1[N - 1];
    for (int u = 0; u < N; ++u) for (auto [w, v] : adj[u])
        if (d1[u] + w + d2[v] == path)
            ans += w;
    cout << ans * 2;
    return 0;
}