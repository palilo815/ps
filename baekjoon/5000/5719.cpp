#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef pair<int, int> p;

const int max_N = 500;
const int INF = 0x3f3f3f3f;

vector<p> adj[max_N];
vector<int> parent[max_N];
int dist[max_N];

void Dijkstra(int N, int src, int dst, int record) {
    memset(dist, 0x3f, sizeof(int) * N);
    dist[src] = 0;

    priority_queue<p, vector<p>, greater<p>> pq;
    pq.emplace(0, src);

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (dist[u] < d) continue;
        if (u == dst) return;

        for (auto [w, v] : adj[u]) {
            int D = d + w;
            if (dist[v] > D) {
                dist[v] = D;
                pq.emplace(D, v);
                if (record) {
                    parent[v].clear();
                    parent[v].emplace_back(u);
                }
            }
            else if (dist[v] == D && record)
                parent[v].emplace_back(u);
        }
    }
}
void erase_edges(int src, int dst) {
    if (dst == src) return;
    for (int u : parent[dst]) {
        for (auto& [w, v] : adj[u]) {
            if (v == dst) {
                w = INF;
                break;
            }
        }
        erase_edges(src, u);
    }
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, M, src, dst;
    while (1) {
        cin >> N >> M;
        if (N == 0) break;
        cin >> src >> dst;
        loop(i, N) adj[i].clear();
        loop(i, N) parent[i].clear();

        while (M--) {
            int u, v, w; cin >> u >> v >> w;
            adj[u].emplace_back(w, v);
        }

        Dijkstra(N, src, dst, 1);
        erase_edges(src, dst);
        Dijkstra(N, src, dst, 0);

        cout << (dist[dst] == INF ? -1 : dist[dst]) << '\n';
    }
    return 0;
}