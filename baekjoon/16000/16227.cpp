#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> p;

const int max_N = 1000;

int dist[max_N + 2];
vector<p> adj[max_N + 2];

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, M; cin >> N >> M;
    while (M--) {
        int u, v, w; cin >> u >> v >> w;
        if (w > 100) continue;
        adj[u].push_back({ w,v });
        adj[v].push_back({ w,u });
    }

    for (int i = 1; i <= N + 1; ++i)
        dist[i] = INT_MAX;

    priority_queue<p, vector<p>, greater<p>> pq;
    pq.push({ 0,0 });
    while (1) {
        auto [d, u] = pq.top(); pq.pop();
        if (u == N + 1) break;
        if (dist[u] < d) continue;
        for (auto [w, v] : adj[u]) {
            int D = w + d;
            if (v != N + 1) D += 5;
            if (dist[v] > D) {
                dist[v] = D;
                pq.push({ D,v });
            }
        }
    }
    cout << dist[N + 1];
    return 0;
}