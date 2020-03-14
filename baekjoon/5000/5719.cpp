#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef pair<int, int> p;
const int max_N = 500;

vector<p> adj[max_N];
vector<int> parent[max_N];
int dist[max_N];

// flag == true면 parent 정보를 기록한다.
void Dijkstra(int N, int src, int dst, bool flag) {
    fill(dist, dist + N, INT_MAX);
    dist[src] = 0;

    priority_queue<p, vector<p>, greater<p>> pq;
    pq.emplace(0, src);

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (dist[u] < d) continue;
        if (u == dst) return;

        // u -> v로 가는 최단경로를 새로 발견하면 parent를 새로 적고
        // 같은 길이의 최단경로를 또 발견하면, parent에 추가로 넣는다.
        for (auto [w, v] : adj[u]) {
            int D = d + w;
            if (dist[v] > D) {
                dist[v] = D;
                pq.emplace(D, v);
                if (flag) {
                    parent[v].clear();
                    parent[v].emplace_back(u);
                }
            }
            else if (dist[v] == D && flag)
                parent[v].emplace_back(u);
        }
    }
}

// parent[dst]를 전부 지운다.
void erase_edges(int src, int dst) {
    if (dst == src) return;

    // u -> dst로 가는 edge를 지운다.
    for (int u : parent[dst]) {
        for (auto it = adj[u].begin(); it != adj[u].end(); ++it)
            if (it->second == dst) {
                adj[u].erase(it);
                break;
            }
        // u에서 다시 재귀호출
        erase_edges(src, u);
    }
}
int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, M, src, dst;
    while (1) {
        // ** initialize **
        // N개의 adj, parent를 초기화한다.
        cin >> N >> M;
        if (N == 0) break;
        cin >> src >> dst;
        loop(i, N) adj[i].clear();
        loop(i, N) parent[i].clear();

        // ** input **
        while (M--) {
            int u, v, w; cin >> u >> v >> w;
            adj[u].emplace_back(w, v);
        }

        // 첫 번째 Dijkstra
        Dijkstra(N, src, dst, true);

        // 위에서 얻은 parent 정보를 이용, edge를 지운다.
        erase_edges(src, dst);

        // 두 번째 Dijkstra
        Dijkstra(N, src, dst, false);

        cout << (dist[dst] == INT_MAX ? -1 : dist[dst]) << '\n';
    }
    return 0;
}