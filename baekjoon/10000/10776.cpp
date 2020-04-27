#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> p;
typedef tuple<int, int, int> tup;

const int max_N = 2000;
const int max_K = 200;

vector<tup> adj[max_N + 1];
p dist[max_N + 1];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int K, N, M; cin >> K >> N >> M;
    while (M--) {
        int u, v, t, h; cin >> u >> v >> t >> h;
        adj[u].emplace_back(t, h, v);
        adj[v].emplace_back(t, h, u);
    }
    int src, dst; cin >> src >> dst;

    memset(dist, 0x3f, sizeof(dist));
    priority_queue<tup, vector<tup>, greater<tup>> pq;
    pq.emplace(0, 0, src);

    int ans = -1;
    while (!pq.empty()) {
        auto [d, h, u] = pq.top(); pq.pop();
        if (u == dst) { ans = d; break; }

        for (auto [w1, w2, v] : adj[u]) {
            int D = d + w1, H = h + w2;
            if (H >= K) continue;

            int flag = 0;
            if (dist[v].first > D) dist[v].first = D, flag = 1;
            if (dist[v].second > H) dist[v].second = H, flag = 1;
            if (flag) pq.emplace(D, H, v);
        }
    }
    cout << ans;
    return 0;
}