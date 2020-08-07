#include <bits/stdc++.h>
using namespace std;

const int mx = 20001;

int dist[mx];
vector<int> adj[mx];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, M; cin >> N >> M;
    for (int u, v; M--;) {
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    memset(dist + 2, 0x3f, sizeof(int) * (N - 1));
    queue<int> q;
    q.emplace(1);

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int& v : adj[u])
            if (dist[v] > dist[u] + 1) {
                dist[v] = dist[u] + 1;
                q.emplace(v);
            }
    }

    int v = 1, cnt = 1;
    for (int i = 2; i <= N; ++i)
        if (dist[i] > dist[v]) v = i, cnt = 1;
        else if (dist[i] == dist[v]) ++cnt;
    cout << v << ' ' << dist[v] << ' ' << cnt;
    return 0;
}