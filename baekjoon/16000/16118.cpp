#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> p;
typedef tuple<int, int, int> tup;

const int max_N = 4000;

int dist[3][max_N + 1];
vector<p> adj[max_N + 1];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, M; cin >> N >> M;
    while (M--) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].emplace_back(w, v);
        adj[v].emplace_back(w, u);
    }

    for (int i = 0; i < 3; ++i)
        fill(dist[i] + 1, dist[i] + N + 1, INT_MAX);
    dist[0][1] = dist[1][1] = 0;

    priority_queue<tup, vector<tup>, greater<tup>>pq;
    pq.emplace(0, 1, 1), pq.emplace(0, 1, 0);

    while (!pq.empty()) {
        auto [d, u, speed] = pq.top(); pq.pop();
        if (dist[speed][u] < d) continue;

        int cost = pow(2, speed);
        speed = 2 - speed;

        for (auto [w, v] : adj[u]) {
            int D = d + w * cost;
            if (dist[speed][v] > D) {
                dist[speed][v] = D;
                pq.emplace(D, v, speed);
            }
        }
    }

    int ans = 0;
    for (int i = 1; i <= N; ++i)
        if (dist[1][i] < min(dist[0][i], dist[2][i]))
            ++ans;
    cout << ans;
    return 0;
}