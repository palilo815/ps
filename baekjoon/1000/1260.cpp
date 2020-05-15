#include <bits/stdc++.h>
using namespace std;

const int max_N = 1001;

vector<int> adj[max_N];
bool visited[max_N];

void DFS(int u) {
    visited[u] = true;
    cout << u << ' ';
    for (int v : adj[u]) if (!visited[v])
        DFS(v);
}
void BFS(int src) {
    cout << '\n';
    memset(visited, 0, sizeof(visited));
    visited[src] = true;

    queue<int> q;
    q.emplace(src);

    while (!q.empty()) {
        int u = q.front(); q.pop();
        cout << u << ' ';

        for (int v : adj[u]) if (!visited[v]) {
            visited[v] = true;
            q.emplace(v);
        }
    }
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, M, src; cin >> N >> M >> src;
    while (M--) {
        int u, v; cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    for (int i = 1; i <= N; ++i)
        sort(adj[i].begin(), adj[i].end());
    
    DFS(src);
    BFS(src);
    return 0;
}