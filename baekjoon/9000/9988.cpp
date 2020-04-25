#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef pair<int, int> p;

const int max_N = 250;

int adj[max_N][max_N];
int dist[max_N];
int parent[max_N];

int Dijkstra(int N, int record) {
    memset(dist, 0x3f, sizeof(int) * N);
    dist[0] = 0;

    priority_queue<p, vector<p>, greater<p>> pq;
    pq.emplace(0, 0);

    while (1) {
        auto [d, u] = pq.top(); pq.pop();
        if (dist[u] < d) continue;
        if (u == N - 1) return d;

        loop(v, N) {
            int D = d + adj[u][v];
            if (dist[v] > D) {
                dist[v] = D;
                pq.emplace(D, v);
                if (record) parent[v] = u;
            }
        }
    }
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    memset(adj, 0x3f, sizeof(adj));
    int N, M; cin >> N >> M;
    while (M--) {
        int u, v, w; cin >> u >> v >> w;
        --u, --v;
        adj[u][v] = adj[v][u] = w;
    }

    int path = Dijkstra(N, 1);
    int ans = 0;

    int v = N - 1;
    while (v) {
        int u = parent[v];
        adj[u][v] *= 2, adj[v][u] *= 2;
        ans = max(ans, Dijkstra(N, 0) - path);
        adj[u][v] /= 2, adj[v][u] /= 2;
        v = u;
    }
    cout << ans;
    return 0;
}