#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> p;
typedef tuple<int, int, int> tup;

const int max_N = 4000;

int dist[max_N + 1][3];
vector<p> adj[max_N + 1];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, M; cin >> N >> M;
    while (M--) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].emplace_back(w, v);
        adj[v].emplace_back(w, u);
    }

    fill(&dist[1][0], &dist[N + 1][0], INT_MAX);
    dist[1][0] = dist[1][1] = 0;

    priority_queue<tup, vector<tup>, greater<tup>>pq;
    pq.emplace(0, 1, 1), pq.emplace(0, 1, 0);

    while (!pq.empty()) {
        auto [d, u, speed] = pq.top(); pq.pop();
        if (dist[u][speed] < d) continue;

        int cost = pow(2, speed);
        speed = 2 - speed;

        for (auto [w, v] : adj[u]) {
            int D = d + w * cost;
            if (dist[v][speed] > D) {
                dist[v][speed] = D;
                pq.emplace(D, v, speed);
            }
        }
    }

    int ans = 0;
    for (int i = 1; i <= N; ++i)
        if (dist[i][1] < min(dist[i][0], dist[i][2]))
            ++ans;
    cout << ans;
    return 0;
}