#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> P;
const int max_V = 100;

vector<P> adj[max_V + 1];
int item[max_V + 1];
int dist[max_V + 1];

int Dijkstra(int V, int src, int limit)
{
    for (int i = 1; i <= V; ++i)
        dist[i] = INT_MAX;
    dist[src] = 0;

    priority_queue<P, vector<P>, greater<P>> pq;
    pq.push({ 0,src });
    while (!pq.empty()) {
        int d = pq.top().first, u = pq.top().second; pq.pop();

        if (d > limit) break;
        if (d > dist[u]) continue;

        for (P p : adj[u]) {
            int D = d + p.first, v = p.second;
            if (dist[v] > D) {
                dist[v] = D;
                pq.push({ D,v });
            }
        }
    }
    int ret = 0;
    for (int i = 1; i <= V; ++i)
        if (dist[i] <= limit)
            ret += item[i];
    return ret;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int V, limit, E;
    cin >> V >> limit >> E;
    for (int i = 1; i <= V; ++i)
        cin >> item[i];
    while (E--) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({ w,v });
        adj[v].push_back({ w,u });
    }

    int ans = 0;
    for (int i = 1; i <= V; ++i)
        ans = max(ans, Dijkstra(V, i, limit));
    cout << ans;
    return 0;
}