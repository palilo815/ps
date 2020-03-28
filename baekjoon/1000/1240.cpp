#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> p;

const int max_N = 1000;

vector<p> adj[max_N + 1];
int dist[max_N + 1];
int parent[max_N + 1];
int depth[max_N + 1];

void DFS(int u, int p, int d) {
    parent[u] = p;
    depth[u] = d;
    for (auto [w, v] : adj[u]) if (v != p) {
        dist[v] = w;
        DFS(v, u, d + 1);
    }
}
int main(){
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, M; cin >> N >> M;
    for (int i = 1; i < N; ++i) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].emplace_back(w, v);
        adj[v].emplace_back(w, u);
    }

    DFS(1, 0, 1);

    while (M--) {
        int u, v; cin >> u >> v;
        int ans = 0;
        while (u != v) {
            if (depth[u] < depth[v]) {
                ans += dist[v];
                v = parent[v];
            }
            else if (depth[u] > depth[v]) {
                ans += dist[u];
                u = parent[u];
            }
            else {
                ans += dist[u] + dist[v];
                u = parent[u], v = parent[v];
            }
        }
        cout << ans << '\n';
    }
    return 0;
}