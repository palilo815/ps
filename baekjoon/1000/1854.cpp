#include <bits/stdc++.h>
#define LOOP(i,n) for(int i=1;i<=n;++i)
using namespace std;
typedef pair<int, int> P;
const int max_N = 1000;

vector<P> adj[max_N + 1];
priority_queue<int> dist[max_N + 1];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, M, k;
    cin >> N >> M >> k;

    while (M--) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].push_back({ v,w });
    }
    
    priority_queue<P, vector<P>, greater<P>> pq;
    pq.push({ 0,1 });
    dist[1].push(0);

    while (!pq.empty()) {
        int u = pq.top().second, d = pq.top().first; pq.pop();
        for (P edge : adj[u]) {
            int v = edge.first, D = d + edge.second;

            // v로 가는 경로가 k개 미만이라면 바로 추가.
            if (dist[v].size() < k) {
                dist[v].push(D);
                pq.push({ D, v });
            }
            // k개라면, D를 포함한 k+1개 경로 중 최댓값을 버려야 한다.
            else if (dist[v].top() > D) {
                dist[v].pop();
                dist[v].push(D);
                pq.push({ D,v });
            }
        }
    }
    
    LOOP(i, N)
        cout << ((dist[i].size() == k) ? dist[i].top() : -1) << '\n';
    return 0;
}