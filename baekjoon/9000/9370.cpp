#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> p;
typedef tuple<int, int, int> tup;

const int max_V = 2000;

vector<p> adj[max_V + 1];
int dist[max_V + 1];
bool possible[max_V + 1];

void Dijkstra(int V, int s, int g, int h) {
    memset(possible, 0, V + 1);
    fill(dist + 1, dist + V + 1, INT_MAX);
    dist[s] = 0;

    priority_queue<tup, vector<tup>, greater<tup>> pq;
    pq.emplace(0, s, 0);

    while (!pq.empty()) {
        auto [d, u, pass] = pq.top(); pq.pop();
        if (dist[u] < d) continue;

        for (auto [w, v] : adj[u]) {
            bool flag = ((u == g && v == h) || (u == h && v == g)) ?
                true : pass;
            int D = d + w;

            if (dist[v] > D) {
                dist[v] = D;
                possible[v] = flag;
                pq.emplace(D, v, flag);
            }
            else if (dist[v] == D && flag) {
                possible[v] = flag;
                pq.emplace(D, v, flag);
            }
        }
    }
}
int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

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

        Dijkstra(V, src, g, h);

        vector<int> ans;
        while (dst--) {
            int x; cin >> x;
            if (possible[x]) ans.emplace_back(x);
        }

        sort(ans.begin(), ans.end());
        for (int x : ans) cout << x << ' ';
        cout << '\n';
    }
    return 0;
}