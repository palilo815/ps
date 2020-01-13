#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)
#define P pair<int,int>

vector<int> Dijkstra(int V, int src, vector<P>(&adj)[1000])
{
    vector<int> dist(V, INT32_MAX);
    dist[src] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push(make_pair(0, src));
    while (!pq.empty()) {
        int cost = pq.top().first, here = pq.top().second;
        pq.pop();
        if (dist[here] < cost) continue;
        loop(i, adj[here].size()) {
            int nextDist = cost + adj[here][i].first;
            int there = adj[here][i].second;
            if (dist[there] > nextDist) {
                dist[there] = nextDist;
                pq.push(make_pair(nextDist, there));
            }
        }
    }
    return dist;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    vector<P> adj[1000], rev[1000];
    int V, E, X;
    cin >> V >> E >> X;
    while (E--) {
        int u, v, w;
        cin >> u >> v >> w;
        --u, --v;
        adj[u].push_back(make_pair(w, v));
        rev[v].push_back(make_pair(w, u));
    }
    // Dijkstra 두번을 정방향, 역방향으로 쓰면
    // 가는 시간과 오는 시간 각각을 구할 수 있음
    vector<int> t1 = Dijkstra(V, X - 1, adj);
    vector<int> t2 = Dijkstra(V, X - 1, rev);
    int ans = 0;
    loop(i, V)
        ans = max(ans, t1[i] + t2[i]);
    cout << ans;
    return 0;
}