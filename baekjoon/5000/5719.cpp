#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef pair<int, int> P;
const int max_N = 500;

vector<P> adj[max_N];
vector<int> parent[max_N];
int dist[max_N];

// flag == true면 parent 정보를 기록한다.
void Dijkstra(int src, int dst, bool flag)
{
    dist[src] = 0;
    priority_queue<P, vector<P>, greater<P>> pq;
    pq.push({ 0,src });
    while (!pq.empty()) {
        int u = pq.top().second, d = pq.top().first; pq.pop();
        if (dist[u] < d) continue;
        if (u == dst) return;
        
        // u -> v로 가는 최단경로를 새로 발견하면 parent를 새로 적고
        // 같은 길이의 최단경로를 또 발견하면, parent에 추가로 넣는다.
        for (P p : adj[u]) {
            int v = p.first, D = d + p.second;
            if (dist[v] > D) {
                dist[v] = D;
                pq.push({ D,v });
                if (flag) {
                    parent[v].clear();
                    parent[v].push_back(u);
                }
            }
            else if (dist[v] == D && flag)
                parent[v].push_back(u);
        }
    }
}

// parent[dst]를 전부 지운다.
void erase_edges(int src, int dst)
{
    if (dst == src) return;

    // u -> dst로 가는 edge를 지운다.
    for (int u : parent[dst]) {
        for (auto it = adj[u].begin(); it != adj[u].end(); ++it)
            if (it->first == dst) {
                adj[u].erase(it);
                break;
            }
        // u에서 다시 재귀호출
        erase_edges(src, u);
    }
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    while (1) {
        // ** initialize **
        // N개의 adj, parent를 초기화한다.
        int N, M, src, dst;
        cin >> N >> M;
        if (N == 0) break;
        cin >> src >> dst;
        loop(i, N) adj[i].clear();
        loop(i, N) parent[i].clear();

        // ** input **
        while (M--) {
            int u, v, w; cin >> u >> v >> w;
            adj[u].push_back({ v,w });
        }

        // 첫 번째 Dijkstra
        loop(i, N) dist[i] = INT_MAX;
        Dijkstra(src, dst, true);

        // 위에서 얻은 parent 정보를 이용, edge를 지운다.
        erase_edges(src, dst);

        // 두 번째 Dijkstra
        loop(i, N) dist[i] = INT_MAX;
        Dijkstra(src, dst, false);

        if (dist[dst] == INT_MAX) cout << -1 << '\n';
        else cout << dist[dst] << '\n';
    }
    return 0;
}