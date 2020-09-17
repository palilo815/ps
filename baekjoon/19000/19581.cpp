#include <bits/stdc++.h>
using namespace std;
struct edge {
    int v, w;
    edge(int v, int w) : v(v), w(w) {}
};

const int mxN = 1e5;

vector<edge> adj[mxN];
int N, dist[mxN];

int* bfs(int src, int ign = -1) {
    fill(dist, dist + N, INT_MAX);
    dist[src] = 0;
    if (~ign) dist[ign] = 0;

    queue<int> q;
    q.emplace(src);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (auto& [v, w] : adj[u])
            if (dist[v] == INT_MAX) {
                dist[v] = dist[u] + w;
                q.emplace(v);
            }
    }
    return max_element(dist, dist + N);
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    cin >> N;
    for (int u, v, w, i = 1; i < N; ++i) {
        cin >> u >> v >> w;
        --u, --v;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    int u = bfs(0) - dist;
    int v = bfs(u) - dist;
    int d1 = *bfs(u, v), d2 = *bfs(v, u);
    cout << max(d1, d2);
    return 0;
}