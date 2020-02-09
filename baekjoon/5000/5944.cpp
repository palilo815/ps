#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> p;

const int max_V = 100000;

vector<p> adj[max_V + 1];
bool visited[max_V + 1];
// int array 따위 필요 없다!

int Dijkstra(int src, int dst)
{
    memset(visited, 0, sizeof(visited));
    priority_queue<p, vector<p>, greater<p>> pq;
    pq.push({ 0,src });
    while (1) {
        auto [d, u] = pq.top(); pq.pop();
        if (visited[u]) continue;
        if (u == dst) return d;
        visited[u] = true;
        for (auto [D, v] : adj[u]) {
            if (visited[v]) continue;
            pq.push({ d + D,v });
        }
    }
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int V, E, src, d1, d2;
    cin >> E >> V >> src >> d1 >> d2;
    while (E--) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].push_back({ w,v });
        adj[v].push_back({ w,u });
    }

    int dist_mid = Dijkstra(d1, d2);
    cout << min(Dijkstra(src, d1), Dijkstra(src, d2)) + dist_mid;
    return 0;
}