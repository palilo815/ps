#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> p;

const int max_N = 1000;

int N;
vector<p> adj[max_N + 1];
int dist[max_N + 1];
int parent[max_N + 1];

int Dijkstra(bool flag) {
    fill(dist + 1, dist + N + 1, INT_MAX);
    priority_queue<p, vector<p>, greater<p>> pq;
    pq.emplace(0, 1);
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (dist[u] < d) continue;
        if (u == N) return d;

        for (auto [w, v] : adj[u]) {
            int D = d + w;
            if (dist[v] > D) {
                dist[v] = D;
                pq.emplace(D, v);
                if (flag) parent[v] = u;
            }
        }
    }
    return -1;
}
int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int M; cin >> N >> M;
    while (M--) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].emplace_back(w, v);
        adj[v].emplace_back(w, u);
    }

    Dijkstra(true);
    int min_dist = dist[N];

    int v = N, delay = 0;
    while (v != 1) {
        int u = parent[v];
        p* e1 = NULL, * e2 = NULL;
        for(auto& edge : adj[u])
            if (edge.second == v) {
                e1 = &edge;
                break;
            }
        for (auto& edge : adj[v])
            if (edge.second == u) {
                e2 = &edge;
                break;
            }
        e1->second = -1, e2->second = -1;
        int d = Dijkstra(false);
        if (d == -1) { cout << -1; return 0; }
        else delay = max(delay, d);
        e1->second = v, e2->second = u;
        v = u;
    }
    cout << delay - min_dist;
    return 0;
}