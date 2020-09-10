#include<bits/stdc++.h>
using namespace std;
using p = pair<int, int>;

const int mxN = 1001;

vector<p> adj[mxN], rev[mxN];
int V, E, src;
int d1[mxN], d2[mxN];

void dijkstra(vector<p> adj[], int dist[]) {
    memset(dist + 1, 0x3f, sizeof(int) * V);
    dist[src] = 0;

    priority_queue<p, vector<p>, greater<p>> pq;
    pq.emplace(0, src);

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (dist[u] < d) continue;

        for (auto& [w, v] : adj[u])
            if (dist[v] > dist[u] + w)
                pq.emplace(dist[v] = dist[u] + w, v);
    }
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    cin >> V >> E >> src;
    for (int u, v, w; E--;) {
        cin >> u >> v >> w;
        adj[u].emplace_back(w, v);
        rev[v].emplace_back(w, u);
    }

    dijkstra(adj, d1);
    dijkstra(rev, d2);

    int ans = 0;
    for (int i = 1; i <= V; ++i)
        ans = max(ans, d1[i] + d2[i]);
    cout << ans;
    return 0;
}