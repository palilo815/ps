#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef pair<int, int> P;
const int max_M = 20;

vector<P> adj[max_M];
int dist[max_M], cache[max_M];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    // ** Dijkstra **

    int T; cin >> T;
    for (int t = 1; t <= T; ++t) {
        int N, M; cin >> N >> M;

        loop(i, M) adj[i].clear();
        loop(i, M) dist[i] = INT_MAX;
        memset(cache, -1, sizeof(int) * M);

        while (N--) {
            int u, v, w; cin >> u >> v >> w;
            adj[u].push_back({ v,w });
            adj[v].push_back({ u,w });
        }

        priority_queue<P, vector<P>, greater<P>> pq;
        pq.push({ 0,0 });
        dist[0] = 0;
        while (!pq.empty()) {
            int u = pq.top().second, d = pq.top().first; pq.pop();
            if (u == M - 1) break;
            for (P p : adj[u]) {
                int v = p.first, D = d + p.second;
                if (dist[v] > D) {
                    dist[v] = D;
                    cache[v] = u;
                    pq.push({ D,v });
                }
            }
        }

        cout << "Case #" << t << ": ";
        if (cache[M - 1] == -1) cout << -1;
        else {
            stack<int> stk;
            int idx = M - 1;
            while (idx != -1) {
                stk.push(idx);
                idx = cache[idx];
            }
            while (!stk.empty()) {
                cout << stk.top() << ' ';
                stk.pop();
            }
        }
        cout << '\n';
    }
    return 0;
}