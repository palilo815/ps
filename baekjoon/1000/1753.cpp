#include<bits/stdc++.h>
using namespace std;
typedef pair<int, int> p;

const int max_V = 20000;

vector<p> adj[max_V + 1];
int dist[max_V + 1];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int V, E, src; cin >> V >> E >> src;
    while (E--) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].emplace_back(w, v);
    }
    
    fill(dist + 1, dist + V + 1, INT_MAX);
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

    for (int i = 1; i <= V; ++i)
        if (dist[i] == INT_MAX) cout << "INF\n";
        else cout << dist[i] << '\n';
    return 0;
}