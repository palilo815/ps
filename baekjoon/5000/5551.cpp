#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> p;

const int max_N = 3000;

vector<p> adj[max_N + 1];
int dist[max_N + 1];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, M, K; cin >> N >> M >> K;
    while (M--) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].emplace_back(w, v);
        adj[v].emplace_back(w, u);
    }

    memset(dist, 0x3f, sizeof(dist));
    priority_queue<p, vector<p>, greater<p>> pq;

    while (K--) {
        int k; cin >> k;
        dist[k] = 0;
        pq.emplace(0, k);
    }

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

    int ans = 0;
    for (int u = 1; u <= N; ++u)
        for (auto [w, v] : adj[u])
            ans = max(ans, (dist[u] + dist[v] + w + 1) / 2);
    cout << ans;
    return 0;
}