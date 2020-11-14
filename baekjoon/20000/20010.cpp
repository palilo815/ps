#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e3;
const int INF = 0x3f3f3f3f;

int adj[mxN][mxN], dist[mxN], par[mxN];
bool con[mxN];
vector<pair<int, int>> graph[mxN];

void bfs(int N, int src) {
    memset(dist, -1, sizeof(int) * N);
    dist[src] = 0;

    queue<int> q;
    q.emplace(src);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (auto& [w, v] : graph[u])
            if (dist[v] == -1) {
                dist[v] = dist[u] + w;
                q.emplace(v);
            }
    }
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N, K;
    cin >> N >> K;

    memset(adj, 0x3f, sizeof(adj));
    for (int u, v, w; K--;) {
        cin >> u >> v >> w;
        adj[u][v] = adj[v][u] = min(adj[u][v], w);
    }

    move(adj[0], adj[0] + N, dist);
    dist[0] = INF;
    con[0] = true;

    int mst = 0;
    for (int cnt = N - 1; cnt--;) {
        int k = 0;
        for (int i = 1; i < N; ++i)
            if (!con[i] && dist[i] < dist[k])
                k = i;

        mst += dist[k];
        con[k] = true;
        graph[par[k]].emplace_back(dist[k], k);
        graph[k].emplace_back(dist[k], par[k]);

        for (int i = 1; i < N; ++i)
            if (!con[i] && adj[k][i] < dist[i])
                dist[i] = adj[k][i], par[i] = k;
    }

    bfs(N, 0);
    bfs(N, max_element(dist, dist + N) - dist);

    cout << mst << '\n'
         << *max_element(dist, dist + N);
}