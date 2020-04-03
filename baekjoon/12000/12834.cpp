#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> p;

const int max_V = 1000;
const int INF = 0x3f3f3f3f;

vector<p> adj[max_V + 1];
int d1[max_V + 1], d2[max_V + 1];

void Dijkstra(int src, int V, int dist[]) {
    memset(dist, 0x3f, sizeof(int) * (V + 1));
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

    int N, V, E, dst1, dst2;
    cin >> N >> V >> E >> dst1 >> dst2;

    vector<int> src(N);
    for (int i = 0; i < N; ++i) cin >> src[i];

    while (E--) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].emplace_back(w, v);
        adj[v].emplace_back(w, u);
    }

    Dijkstra(dst1, V, d1);
    Dijkstra(dst2, V, d2);

    int ans = 0;
    for (int idx : src) {
        ans += (d1[idx] == INF ? -1 : d1[idx]);
        ans += (d2[idx] == INF ? -1 : d2[idx]);
    }
    cout << ans;
    return 0;
}