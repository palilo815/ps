#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef pair<int, int> P;
typedef tuple<int, int, bool> tup;
const int max_V = 5000;

vector<P> adj[max_V + 1];
int dist[max_V + 1];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int V, E, gunwoo; cin >> V >> E >> gunwoo;
    while (E--) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].push_back({ w,v });
        adj[v].push_back({ w,u });
    }

    for (int i = 1; i <= V; ++i)
        dist[i] = INT_MAX;
    dist[1] = 0;

    bool ans = false;
    priority_queue<tup, vector<tup>, greater<tup>> pq;
    pq.push({ 0,1,false });
    while (!pq.empty()) {
        int d = get<0>(pq.top()), u = get<1>(pq.top());
        bool save = get<2>(pq.top()); pq.pop();

        if (u == gunwoo) save = true;
        // dst에 도착하더라도,
        // 최딘경로가 여러 개일 수 있으므로 계속 진행해야 한다.
        // 최단경로를 모두 찾았다면 (dist[v] < d) 끝
        if (u == V) {
            if (dist[V] < d) break;
            ans |= save;
            continue;
        }
        if (dist[u] < d) continue;

        // dst로 가는 최단경로가 여러 개일 수 있으므로
        // if(dist[v] > D) 가 아닌 if(dist[v] >= D)로 써야한다.
        for (P p : adj[u]) {
            int D = d + p.first, v = p.second;
            if (dist[v] >= D) {
                dist[v] = D;
                pq.push({ D,v,save });
            }
        }
    }

    if (ans) cout << "SAVE HIM";
    else cout << "GOOD BYE";
    return 0;
}