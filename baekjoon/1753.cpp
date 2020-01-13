#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)
#define P pair<int,int>

vector<P> adj[20000];
void Dijkstra(int V, int src)
{
    vector<int> dist(V, INT32_MAX);
    dist[src] = 0;
    priority_queue<P, vector<P>, greater<P>> pq;
    pq.push(make_pair(0, src));
    while (!pq.empty()) {
        int cost = pq.top().first, here = pq.top().second; pq.pop();
        if (dist[here] < cost) continue;
        loop(i, adj[here].size()) {
            int there = adj[here][i].second;
            int nextDist = cost + adj[here][i].first;
            if (dist[there] > nextDist) {
                dist[there] = nextDist;
                pq.push({ nextDist, there });
            }
        }
    }
    for (int x : dist) {
        if (x == INT32_MAX) cout << "INF";
        else cout << x;
        cout << '\n';
    }
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int V, E, k; cin >> V >> E >> k;
    while (E--) {
        int u, v, w; cin >> u >> v >> w;
        adj[u - 1].push_back({ w, v - 1 });
    }
    Dijkstra(V, k - 1);
    return 0;
}