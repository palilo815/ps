#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)
#define P pair<int,int>
int V;
int adj[801][801], ans[2];

// src에서 m1으로 가는 최단경로를 ans[0]에
// m2로 가는 최단경로를 ans[1]에 저장한다.
void Dijkstra(int src, int m1, int m2)
{
    vector<int> dist(V + 1, INT32_MAX);
    dist[src] = 0;
    priority_queue<P, vector<P>, greater<P>> pq;
    pq.push(make_pair(0, src));
    while (!pq.empty() && (ans[0] == -1 || ans[1] == -1)) {
        int cost = pq.top().first, here = pq.top().second;
        pq.pop();
        if ((here == m1) && (ans[0] == -1)) ans[0] = cost;
        if ((here == m2) && (ans[1] == -1)) ans[1] = cost;
        if (dist[here] < cost) continue;
        for (int i = 1; i <= V; ++i)
            if (adj[here][i]) {
                int nextDist = cost + adj[here][i];
                if (dist[i] > nextDist) {
                    dist[i] = nextDist;
                    pq.push(make_pair(nextDist, i));
                }
            }
    }
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int E, m1, m2;
    cin >> V >> E;
    while (E--) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u][v] = adj[v][u] = w;
    }
    cin >> m1 >> m2;

    // 먼저 m1 -> m2의 길이를 찾아 M에 저장한다.
    ans[0] = ans[1] = -1;
    Dijkstra(m1, m1, m2);
    int M = ans[1], A = 0, B = 0;
    if (M == -1) { cout << "-1"; return 0; }

    // 1부터 m1까지의 거리를 A에
    // 1부터 m2까지의 거리를 B에 저장
    ans[0] = ans[1] = -1;
    Dijkstra(1, m1, m2);
    if (ans[0] == -1 || ans[1] == -1) { cout << -1; return 0; }
    A += ans[0], B += ans[1];

    // V부터 m1까지의 거리를 A에 더하고
    // V부터 m2까지의 거리를 B에 더한다.
    ans[0] = ans[1] = -1;
    Dijkstra(V, m1, m2);
    if (ans[0] == -1 || ans[1] == -1) { cout << -1; return 0; }
    A += ans[1], B += ans[0];

    // A,B중 작은 값 + (m1~m2까지의 거리)가 정답이다. 
    cout << (min(A, B) + M);
    return 0;
}