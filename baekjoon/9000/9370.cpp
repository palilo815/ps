#include <bits/stdc++.h>
#define LOOP(i,n) for(int i=1;i<=n;++i)
#define P pair<int,int>
#define tup tuple<int,int,bool>
using namespace std;
const int max_V = 2000;

vector<P> adj[max_V + 1];
int dist[max_V + 1];
bool passing[max_V + 1];

void Dijkstra(int V, int s, int g, int h)
{
    LOOP(i, V) dist[i] = INT_MAX;
    memset(passing, 0, V + 1);

    // pq : {거리, vertex, g-h를 지났는지 여부}
    priority_queue<tup, vector<tup>, greater<tup>> pq;
    pq.push({ 0,s,false });
    dist[s] = 0;
    while (!pq.empty()) {
        int cost = get<0>(pq.top()), u = get<1>(pq.top());
        bool passed = get<2>(pq.top()); pq.pop();

        if (dist[u] < cost) continue;
        for (P p : adj[u]) {
            int v = p.first, w = p.second;
            bool flag = (u == g && v == h || u == h && v == g) ? true : passed;

            // 새로운 최단경로를 찾은 경우
            if (dist[v] > cost + w) {
                dist[v] = cost + w;
                passing[v] = flag;
                pq.push({ cost + w,v,flag });
            }
            // 거리가 같으나, g-h를 지나는 경로가 있는 경우
            else if (dist[v] == cost + w && flag) {
                passing[v] = flag;
                pq.push({ cost + w, v, flag });
            }
        }
    }
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T; cin >> T;
    while (T--) {
        // ** input **
        int V, E, dst, s, g, h;
        cin >> V >> E >> dst >> s >> g >> h;

        // ** initialize graph **
        LOOP(i, V) adj[i].clear();
        while (E--) {
            int u, v, w; cin >> u >> v >> w;
            adj[u].push_back({ v,w });
            adj[v].push_back({ u,w });
        }
        
        Dijkstra(V, s, g, h);

        // 만약 x로 가는 최단경로가 g-h를 지나간다면
        // 정답에 추가.
        vector<int> ans;
        while (dst--) {
            int x; cin >> x;
            if (passing[x])
                ans.push_back(x);
        }

        // ** print answer **
        sort(ans.begin(), ans.end());
        for (int x : ans)
            cout << x << ' ';
        cout << '\n';
    }
    return 0;
}