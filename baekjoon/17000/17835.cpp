#include<bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
#define ll long long
#define P pair<ll,int>
using namespace std;

vector<P> graph[100001];
ll dist[100001];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int V, E, K; cin >> V >> E >> K;
    for (int i = 1;i <= V;++i)
        dist[i] = INT64_MAX;
    while (E--) {
        int u, v, w; cin >> u >> v >> w;
        graph[v].push_back({ u,w });	// reverse order
    }

    // 면접 장소를 전부 pq에 넣고 Dijkstra로 찾는다.
    priority_queue<P, vector<P>, greater<P>> pq;
    while (K--) {
        int x; cin >> x;
        pq.push({ 0,x });
        dist[x] = 0;
    }
    while (!pq.empty()) {
        ll cost = pq.top().first;
        int here = pq.top().second; pq.pop();
        if (dist[here] < cost) continue;
        loop(i, graph[here].size()) {
            int there = graph[here][i].first;
            ll w = graph[here][i].second;
            if (dist[there] > cost + w) {
                dist[there] = cost + w;
                pq.push({ cost + w,there });
            }
        }
    }

    int ans = 0;
    ll MAX = -1;
    for (int i = 1; i <= V; ++i) {
        if (dist[i] > MAX) {
            MAX = dist[i];
            ans = i;
        }
    }
    cout << ans << '\n' << MAX;
    return 0;
}