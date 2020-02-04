#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef long long ll;
typedef pair<ll, int> P;
const int max_N = 100000;

bool view[max_N];
ll dist[max_N];
vector<P> adj[max_N];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    // ** Dijkstra **

    // max_M = 300,000
    // max_w = 100,000 이므로
    // long long을 사용해야 한다.

    int N, M; cin >> N >> M;
    loop(i, N) cin >> view[i];
    loop(i, N) dist[i] = INT64_MAX;
    view[N - 1] = false;
    dist[0] = 0;
   
    while (M--) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].push_back({ w,v });
        adj[v].push_back({ w,u });
    }

    priority_queue<P, vector<P>, greater<P>> pq;
    pq.push({ 0,0 });
    while (!pq.empty()) {
        ll d = pq.top().first;
        int u = pq.top().second;
        pq.pop();
        
        if (dist[u] < d) continue;
        if (u == N - 1) break;

        for (P p : adj[u]) {
            ll D = d + p.first;
            int v = p.second;
            if (!view[v] && dist[v] > D) {
                dist[v] = D;
                pq.push({ D,v });
            }
        }
    }

    if (dist[N - 1] == INT64_MAX) cout << -1;
    else cout << dist[N - 1];
    return 0;
}