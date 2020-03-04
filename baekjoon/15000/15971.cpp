#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> p;

const int max_N = 100000;

vector<p> adj[max_N + 1];
int dist[max_N + 1];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, src, dst; cin >> N >> src >> dst;
    for (int i = 1; i < N; ++i) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].emplace_back(w, v);
        adj[v].emplace_back(w, u);
    }

    memset(dist, -1, sizeof(dist));
    dist[src] = 0;
    
    queue<p> q;
    q.push({ src,0 });
    while (1) {
        auto [u, _max] = q.front(); q.pop();
        if (u == dst) {
            cout << dist[u] - _max;
            return 0;
        }

        for (auto [w, v] : adj[u]) if (dist[v] == -1) {
            dist[v] = dist[u] + w;
            q.push({ v,max(_max,w) });
        }
    }
    return 0;
}