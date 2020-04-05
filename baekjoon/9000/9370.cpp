#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> p;

const int max_V = 2000;

vector<p> adj[max_V + 1];
int d1[max_V + 1], d2[max_V + 1];

void Dijkstra(int V, int s, int dist[]) {
    memset(dist, 0x3f, sizeof(int) * (V + 1));
    dist[s] = 0;

    priority_queue<p, vector<p>, greater<p>> pq;
    pq.emplace(0, s);

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (dist[u] < d) continue;

        for (auto [w, v] : adj[u]) {
            int D = d + w;
            if (dist[v] > D) {
                dist[v] = D;
                pq.emplace(D, v);
            }
        }
    }
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int T; cin >> T;
    while (T--) {
        int V, E, dst, src, g, h;
        cin >> V >> E >> dst >> src >> g >> h;

        for (int i = 1; i <= V; ++i) adj[i].clear();
        while (E--) {
            int u, v, w; cin >> u >> v >> w;
            adj[u].emplace_back(w, v);
            adj[v].emplace_back(w, u);
        }

        Dijkstra(V, src, d1);

        int m = 0;
        for (auto [w, node] : adj[g]) if (node == h) {
            m = w;
            break;
        }

        vector<int> ans;
        while (dst--) {
            int x; cin >> x;
            Dijkstra(V, x, d2);
            int tmp = d1[x] - m;
            if (d1[g] + d2[h] == tmp || d1[h] + d2[g] == tmp)
                ans.emplace_back(x);
        }

        sort(ans.begin(), ans.end());
        for (int x : ans) cout << x << ' ';
        cout << '\n';
    }
    return 0;
}