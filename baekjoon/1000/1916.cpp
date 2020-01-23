#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)
#define MAX_V 1001
#define P pair<int,int>

int V, E;
vector<P> adj[MAX_V];	//first : distance, second : num of V

int Dijkstra(int src, int dest)
{
    vector<int> dist(V + 1, INT32_MAX);
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
                pq.push(make_pair(nextDist, there));
            }
        }
    }
    return dist[dest];
}

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    cin >> V >> E;
    while (E-- > 0) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back(make_pair(w, v));
    }
    int from, to;
    cin >> from >> to;
    cout << Dijkstra(from, to);
    return 0;
}