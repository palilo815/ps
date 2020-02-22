#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> p;

const int max_N = 40000;

vector<p> adj[max_N + 1];
int parent[max_N + 1];
int height[max_N + 1];
int dist[max_N + 1];

void DFS(int u, int p, int h) {
    parent[u] = p;
    height[u] = h;
    for (auto [v, w] : adj[u]) if (v != p) {
        dist[v] = w;
        DFS(v, u, h + 1);
    }
}
int query(int u, int v) {
    int ret = 0;
    while (u != v) {
        int h_u = height[u], h_v = height[v];
        if (h_u <= h_v) {
            ret += dist[v];
            v = parent[v];
        }
        if (h_u >= h_v) {
            ret += dist[u];
            u = parent[u];
        }
    }
    return ret;
}
int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    for (int i = 0; i < N - 1; ++i) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].push_back({ v,w });
        adj[v].push_back({ u,w });
    }

    DFS(1, -1, 0);

    int Q; cin >> Q;
    while (Q--) {
        int u, v; cin >> u >> v;
        cout << query(u, v) << '\n';
    }
    return 0;
}