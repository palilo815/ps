#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> p;
typedef tuple<int, int, int> tup;

const int max_N = 1000;

int dist[max_N + 2][101];
vector<p> adj[max_N + 2];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, M; cin >> N >> M;
    while (M--) {
        int u, v, w; cin >> u >> v >> w;
        if (w > 100) continue;
        adj[u].emplace_back(w, v);
        adj[v].emplace_back(w, u);
    }

    fill(&dist[0][0], &dist[N + 2][0], INT_MAX);
    dist[0][0] = 0;

    priority_queue<tup, vector<tup>, greater<tup>> pq;
    pq.emplace(0, 0, 0);
    while (1) {
        auto [d, dust, u] = pq.top(); pq.pop();
        if (dist[u][dust] < d) continue;
        if (u == N + 1) { cout << d; break; }

        for (auto [w, v] : adj[u]) {
            int D = d + w;
            if (dust + w <= 100 && dist[v][dust + w] > D) {
                dist[v][dust + w] = D;
                pq.emplace(D, dust + w, v);
            }
            D += 5;
            if (dist[v][w] > D) {
                dist[v][w] = D;
                pq.emplace(D, w, v);
            }
        }
    }
    return 0;
}