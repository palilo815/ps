#include <bits/stdc++.h>
#define loop(i, n) for (int i = 0; i < n; ++i)
using namespace std;

const int mxN = 1e2;
const int NEG = 0xc0c0c0c0;

int adj[mxN][mxN], dist[mxN], par[mxN];
bool visited[mxN];

void bfs(int N) {
    visited[N - 1] = true;

    queue<int> q;
    q.emplace(N - 1);

    while (!q.empty()) {
        int v = q.front();
        q.pop();

        loop(u, N) if (!visited[u] && adj[u][v] != NEG) {
            visited[u] = true;
            q.emplace(u);
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
    int N, M;
    cin >> N >> M;

    memset(adj, 0xc0, sizeof(adj));
    for (int u, v, w; M--;) {
        cin >> u >> v >> w;
        adj[u - 1][v - 1] = max(adj[u - 1][v - 1], w);
    }

    bfs(N);
    if (!visited[0]) return cout << -1, 0;

    memset(par, -1, sizeof(int) * N);
    memset(dist, 0xc0, sizeof(int) * N);
    dist[0] = 0;

    for (int cnt = N - 1; cnt--;) {
        bool update = false;
        loop(u, N) if (visited[u] && dist[u] != NEG) loop(v, N) if (visited[v]) {
            if (adj[u][v] != NEG && dist[v] < dist[u] + adj[u][v]) {
                dist[v] = dist[u] + adj[u][v];
                par[v] = u;
                update = true;
            }
        }
        if (!update) break;
    }

    loop(u, N) if (visited[u] && dist[u] != NEG) loop(v, N) if (visited[v]) {
        if (adj[u][v] != NEG && dist[v] < dist[u] + adj[u][v]) {
            if (visited[v])
                return cout << -1, 0;
        }
    }

    vector<int> path;
    for (int u = N - 1; ~u; u = par[u])
        path.emplace_back(u + 1);
    for (auto it = path.rbegin(); it != path.rend(); ++it)
        cout << *it << ' ';
    return 0;
}