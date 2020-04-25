#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> p;

const int max_V = 2000;

vector<p> adj[max_V + 1];
int dist[max_V + 1];

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
            w *= 2;
            if ((u == g && v == h) || (v == g && u == h)) --w;
            adj[u].emplace_back(w, v);
            adj[v].emplace_back(w, u);
        }

        memset(dist, 0x3e, sizeof(int) * (V + 1));
        dist[src] = 0;

        priority_queue<p, vector<p>, greater<p>> pq;
        pq.emplace(0, src);

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

        vector<int> ans;
        while (dst--) {
            int x; cin >> x;
            if (dist[x] & 1) ans.emplace_back(x);
        }

        sort(ans.begin(), ans.end());
        for (int x : ans) cout << x << ' ';
        cout << '\n';
    }
    return 0;
}