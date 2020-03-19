#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> p;

const int max_N = 5000;

vector<p> adj[max_N + 1];
p dist[max_N + 1];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, M; cin >> N >> M;
    while (M--) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].emplace_back(w, v);
        adj[v].emplace_back(w, u);
    }

    fill(dist + 1, dist + N + 1, make_pair(INT_MAX, INT_MAX));
    dist[1].first = 0;

    priority_queue<p, vector<p>, greater<p>> pq;
    pq.emplace(0, 1);

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (dist[u].second < d) continue;
        if (dist[u].first < d) dist[u].second = d;

        for (auto [w, v] : adj[u]) {
            int D = d + w;
            if (dist[v].first > D) {
                dist[v].first = D;
                pq.emplace(D, v);
            }
            else if (dist[v].first < D && D < dist[v].second) {
                dist[v].second = D;
                pq.emplace(D, v);
            }
        }
    }
    cout << dist[N].second;
    return 0;
}